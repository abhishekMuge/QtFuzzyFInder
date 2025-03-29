#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QFile>
#include <QTextStream>
class SearchWorker : public QThread
{
    Q_OBJECT
public:
    // SearchWorker();
     SearchWorker(const QStringList &files, const QString &query);
signals:
     void matchFound(const QString &filePath);
protected:
     void run() override;

private:
    QStringList files;
    QString query;
private:
    bool fileContainsQuery(const QString &filePath, const QString &query);
    bool fuzzyMatch(const QString &text, const QString &query);
    int levenshteinDistance(const QString &s1, const QString &s2);

};

#endif // SEARCHWORKER_H
