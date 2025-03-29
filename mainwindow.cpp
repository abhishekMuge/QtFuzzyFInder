#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QPushButton *selectDirButton = new QPushButton("Select Directory", this);
    connect(selectDirButton,&QPushButton::clicked, this, &MainWindow::selectDirectory);

    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Enter search query...");
    connect(searchInput, &QLineEdit::returnPressed, this, &MainWindow::performSearch);

    fileList = new QListWidget(this);
    fileList->setSelectionMode(QAbstractItemView::MultiSelection);
    fileList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(fileList, &QListWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    resultDisplay = new QTextEdit(this);
    resultDisplay->setReadOnly(true);

    layout->addWidget(selectDirButton);
    layout->addWidget(searchInput);
    layout->addWidget(fileList);
    layout->addWidget(resultDisplay);

    setCentralWidget(centralWidget);
    LoadAppInfoSetting();
    // ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_SelectFolderBtnClick()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Select Folder"), QString(),
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!folder.isEmpty()) {
        // ui->label->setText(folder); // Assuming you have a QLabel named label in your UI
        qDebug() << folder;
        QString str1 = "Kitten";
        QString str2 = "sitting";
        qDebug() << levenshteinDistance(str1, str2);
    } else {
        QMessageBox::warning(this, tr("No Folder Selected"), tr("Please select a valid folder."));
    }
}
int MainWindow::levenshteinDistance(const QString &str1, const QString &str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a 2D table to store distances
    QVector<QVector<int>> dp(m + 1, QVector<int>(n + 1));

    // Initialize base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i; // Cost of deleting all characters
    for (int j = 0; j <= n; j++) dp[0][j] = j; // Cost of inserting all characters

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No cost if characters match
            } else {
                dp[i][j] = 1 + qMin(qMin(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]); // Corrected qMin usage
            }
        }
    }

    return dp[m][n];
}

void MainWindow::selectDirectory() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory");
    if (!dir.isEmpty()) {
        SetAppInfoSetting(dir);
        scanFiles(dir);
    }
}

void MainWindow::scanFiles(const QString &directory) {
    fileList->clear();
    QDirIterator it(directory, {"*.txt", "*.pdf"}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filePath = it.next();
        QListWidgetItem *item = new QListWidgetItem(filePath, fileList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked); // Default checked
        fileList->addItem(item);
    }
}
void MainWindow::performSearch() {
    QString query = searchInput->text();
    if (query.isEmpty()) return;

    resultDisplay->clear();
    QStringList selectedFiles;
    for (int i = 0; i < fileList->count(); ++i) {
        QListWidgetItem *item = fileList->item(i);
        if (item->checkState() == Qt::Checked) { // Only search in checked files
            // QString filePath = item->text();
            // if (fileContainsQuery(filePath, query)) {
            //     resultDisplay->append("Match found in: " + filePath);
            // }
            selectedFiles.append(item->text());
        }
    }
    SearchWorker *worker = new SearchWorker(selectedFiles, query);
    connect(worker, &SearchWorker::matchFound, this, &MainWindow::displayMatch);
    connect(worker, &QThread::finished, worker, &QObject::deleteLater);
    worker->start();
}
void MainWindow::displayMatch(const QString &filePath) {
    resultDisplay->append("Match found in: " + filePath);
}
bool MainWindow::fileContainsQuery(const QString &filePath, const QString &query) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (fuzzyMatch(line, query)) {
            return true;
        }
    }
    return false;
}

bool MainWindow::fuzzyMatch(const QString &text, const QString &query) {
    return text.contains(query, Qt::CaseInsensitive); // Placeholder for fuzzy search
}
void MainWindow::LoadAppInfoSetting()
{
    QSettings setting("QTDEV", "FuzzyFinder");
    QString lastOpenDirectory = setting.value("lastDirectory", "").toString();
    if (!lastOpenDirectory.isEmpty())
    {
        scanFiles(lastOpenDirectory);
    }
}
void MainWindow::SetAppInfoSetting(QString &dirInfo)
{
    QSettings setting("QTDEV", "FuzzyFinder");
    setting.setValue("lastDirectory", dirInfo);
}
void MainWindow::showContextMenu(const QPoint &pos) {
    QMenu contextMenu(this);
    QAction *selectAllAction = contextMenu.addAction("Select All");
    QAction *deselectAllAction = contextMenu.addAction("Deselect All");

    connect(selectAllAction, &QAction::triggered, this, &MainWindow::selectAllFiles);
    connect(deselectAllAction, &QAction::triggered, this, &MainWindow::deselectAllFiles);

    contextMenu.exec(fileList->viewport()->mapToGlobal(pos));
}

void MainWindow::selectAllFiles() {
    for (int i = 0; i < fileList->count(); ++i) {
        fileList->item(i)->setCheckState(Qt::Checked);
    }
}

void MainWindow::deselectAllFiles() {
    for (int i = 0; i < fileList->count(); ++i) {
        fileList->item(i)->setCheckState(Qt::Unchecked);
    }
}
