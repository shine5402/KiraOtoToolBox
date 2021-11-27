#include "vowelcrossfadingotolistmodifyworker.h"
#include <utils/misc/fplusAdapter.h>

VowelCrossfadingOtoListModifyWorker::VowelCrossfadingOtoListModifyWorker(QObject* parent):OtoListModifyWorker(parent)
{

}


bool VowelCrossfadingOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                 OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    resultOtoList = srcOtoList;

    auto CVList = options.getOption("CVList").toStringList();
    auto VList = options.getOption("VList").toStringList();
    auto longRecordingPattern = options.getOption("longRecordingPattern").toStringList();
    auto longRecordingList = fplus::unique(
                    fplus::transform_and_concat(
                        [longRecordingPattern](const QString& alias)->QList<QString>{
        return fplus::transform([alias](QString pattern)->QString{
            return pattern.replace("%a", alias);
        }, longRecordingPattern);
    }, CVList + VList));

    if (options.getOption("doCVCrossfading").toBool())
    {
        auto preUtterance = options.getOption("CVPreUtterance").toDouble();
        auto overlap = options.getOption("CVOverlap").toDouble();
        auto matchList = CVList + longRecordingList;
        QMutableVectorIterator it(resultOtoList);
        while (it.hasNext()){
            auto entry = it.next();
            if (matchList.contains(it.value().alias()))
            {
                entry.setPreUtterance(preUtterance);
                entry.setOverlap(overlap);
                if (options.getOption("CVBehaviourOverride").toBool()){
                    it.setValue(entry);
                }
                if (options.getOption("CVBehaviourCopy").toBool())
                {
                    entry.setAlias(QLatin1String("* %1").arg(entry.alias()));
                    it.insert(entry);
                }
            }
        }
    }

    if (options.getOption("VVOverlapIncrease").toBool()){
        auto VVList = fplus::transform_and_concat([VList](const QString& CV)->QList<QString>{
            return fplus::transform([CV](const QString& V)->QString{
                return V + " " + CV;
            }, VList);
        }, CVList);

        resultOtoList = fplus::transform([VVList](OtoEntry entry){
            if (VVList.contains(entry.alias())){
                entry.setOverlap(entry.preUtterance() / 2);
            }
                return entry;
        }, resultOtoList);
    }

    return true;
}
