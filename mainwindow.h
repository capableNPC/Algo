#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include "datapackage.h"
#include "module/AlgorithmModule/algoCfgWindow/algocfgwindow.h"
#include "module/AlgorithmModule/algoExplain/algoexplain.h"
#include "module/AlgorithmModule/algoCompute/structcompute.h"
#include "module/CanvaModule/canva.h"
#include "module/DrawModule/brush.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace data;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Config* config;
    StructCompute* structCompute;

    //AlgoTypes algoType;
//<menu>
    QMenu * menu[5];
    QAction * startAction;
    QAction * stopAction;
    QAction * finishAction;
    QAction * debugAction;
    QMenu * rateMenu;
    QAction * rate_x0_Action;//慢速
    QAction * rate_x1_Action;//正常
    QAction * rate_x2_Action;//快速
    QAction * rate_x3_Action;//超快
    QAction * algoTreeWindowAction;
    QAction * algoDetailsWindowAction;
    QAction * controlWindowAction;
    QAction * debugWindowAction;
    QAction * normalFrameAction;
    QAction * hugeFrameAction;
    QAction * frameSetAction;
    QAction * themeSetAction;
    //QAction * toolAction;
    QAction * recodScreenAction;
    QAction * outPutAction;
    QAction * helpAction;
    QAction * aboutAction;

    void initMenuBar();
//</menu>

//<status>
    QLabel * version;
    void initStatusBar();
//</status>

//<algoTree>

    AlgoTypes SelectedType = None;
    QList<QTreeWidgetItem *> rootList;
    QString algoTreeDataPath;
    void initAlgoTree();
    void parsingAlgoTreeXML(QXmlStreamReader &reader, QTreeWidgetItem* node);
//</algoTree>

//<algoExplain>
    AlgoExplain* explainUpdater;
    void initExplainDock();
//</algoExplain>

//<Canva>
    Canva* canva;
    Brush* brush;
    void initCanva();
//</Canva>

private:
    void init();
    void loadQss();
    void algoDemoStart();
    void UILock(bool state);
    void createConnects();
    void configClear();

private slots:
    void on_algoTree_itemDoubleClicked(QTreeWidgetItem* node);

    void on_algoTree_itemSelectionChanged();
    void on_explainBox_currentChanged(int index);
    void killComputeThread();
};
#endif // MAINWINDOW_H
