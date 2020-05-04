#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    this->resize(QApplication::desktop()->width() * 5.0/6,
                 (QApplication::desktop()->height()-50) * 4.0/5);//任务栏高度50
    this->move((QApplication::desktop()->width() - this->width())/2,
               ((QApplication::desktop()->height()-50) - this->height())/2);
    ui->algoControlDock->hide();
    //ui->dataControlDock->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    version = new QLabel("0.0.001");
    //algoTreeDataPath = "";
    config = new Config;
    initCanva();
    loadQss();
    initMenuBar();
    initStatusBar();
    initAlgoTree();
    initExplainDock();
    createConnects();
}

void MainWindow::createConnects()
{
    connect(finishAction,&QAction::triggered,this,&MainWindow::killComputeThread);
}

void MainWindow::configClear()
{
    config->data.clear();
    config->order = OrderType::chaos;
    config->fill = false;
    config->normalView = true;
    config->configState = false;
    config->hasArrow = false;
}

void MainWindow::initCanva()
{
    canva = new Canva(this);
    QHBoxLayout* lytH = new QHBoxLayout;
    QVBoxLayout* lytV = new QVBoxLayout;
    lytV->addLayout(lytH);
    lytH->addWidget(canva);
    ui->centralwidget->setLayout(lytV);
    //this->setLayout(lytV);
    //this->setCentralWidget(canva);
}

void MainWindow::loadQss()
{
    QFile qss("./qss/default.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet("");
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::algoDemoStart()
{
    UILock(true);
    qDebug() << "algoDemoStart" << endl;
    structCompute = new StructCompute(this,config,SelectedType);
    brush = new Brush(this,canva,config);
    connect(brush,&Brush::Brush2Canva,canva,&Canva::DataOfBrush);
    brush->start();

    //connect(structCompute, static_cast<void(StructCompute::*)(QVector<DataOfLinear>)>(&StructCompute::initCanva),brush,static_cast<void(Brush::*)(QVector<DataOfLinear>)>(&Brush::initCanva));
    connect(structCompute,SIGNAL(initCanva(QVector<DataOfLinear>)),brush,SLOT(initCanva(QVector<DataOfLinear>)));
    qDebug() << "strCom" << endl;
    structCompute->start();
    qDebug() << "algoDemoEnd" << endl;
}

void MainWindow::UILock(bool state)
{
    ui->algoTree->setEnabled(!state);
    startAction->setEnabled(!state);
    stopAction->setEnabled(state);
    finishAction->setEnabled(state);
//    singleStepAction->setEnabled(true);
//    autoStepAction->setEnabled(true);
//    autoStepAction->setChecked(true);
    rateMenu->setEnabled(state);

    normalFrameAction->setEnabled(state);
    hugeFrameAction->setEnabled(state);
    frameSetAction->setEnabled(!state);
    themeSetAction->setEnabled(!state);
    recodScreenAction->setEnabled(state);
    outPutAction->setEnabled(state);
}

void MainWindow::initMenuBar()
{
//初始化Action开始
    startAction = new QAction(QIcon(""),tr("开始"),this);
    //startAction->setShortcuts(Qt::CTRL);
    startAction->setStatusTip(tr("开始算法演示"));
    stopAction = new QAction(QIcon(""),tr("暂停"),this);
    //stopAction->setShortcuts(Qt::CTRL);
    stopAction->setStatusTip(tr("暂停算法演示"));
    finishAction = new QAction(QIcon(""),tr("终止"),this);
    //finishAction->setShortcuts(Qt::CTRL);
    finishAction->setStatusTip(tr("终止算法演示"));
    rateMenu = new QMenu(tr("倍速(&R)"), this);
    //rateMenu->setShortcuts(Qt::CTRL);
    rateMenu->setStatusTip(tr("设置算法演示倍速"));
    rate_x0_Action = new QAction(QIcon(""),tr("慢速"),this);
    //rate_x0_Action->setShortcuts(Qt::CTRL);
    rate_x0_Action->setStatusTip(tr("设置算法演示倍速为慢速"));
    rate_x1_Action = new QAction(QIcon(""),tr("正常"),this);
    //rate_x1_Action->setShortcuts(Qt::CTRL);
    rate_x1_Action->setStatusTip(tr("设置算法演示倍速为正常"));
    rate_x2_Action = new QAction(QIcon(""),tr("快速"),this);
    //rate_x2_Action->setShortcuts(Qt::CTRL);
    rate_x2_Action->setStatusTip(tr("设置算法演示倍速为快速"));
    rate_x3_Action = new QAction(QIcon(""),tr("超快"),this);
    //rate_x3_Action->setShortcuts(Qt::CTRL);
    rate_x3_Action->setStatusTip(tr("设置算法演示倍速为超快"));
    //windowsAction = new QAction(QIcon(""),tr("窗口"),this);
    //windowsAction->setShortcuts(Qt::CTRL);
    //windowsAction->setStatusTip(tr("窗口选项"));
    algoTreeWindowAction = new QAction(QIcon(""),tr("算法树"),this);
    //algoTreeWindowAction->setShortcuts(Qt::CTRL);
    algoTreeWindowAction->setStatusTip(tr("展示算法树窗口"));
    algoDetailsWindowAction = new QAction(QIcon(""),tr("算法详情"),this);
    //algoDetailsWindowAction->setShortcuts(Qt::CTRL);
    algoDetailsWindowAction->setStatusTip(tr("展示算法详情窗口"));
    controlWindowAction = new QAction(QIcon(""),tr("控制"),this);
    //controlWindowAction->setShortcuts(Qt::CTRL);
    controlWindowAction->setStatusTip(tr("展示控制窗口"));
    debugWindowAction = new QAction(QIcon(""),tr("算法详情"),this);
    //algoCodeDetailWindowAction->setShortcuts(Qt::CTRL);
    debugWindowAction->setStatusTip(tr("展示算法详情窗口"));
    normalFrameAction = new QAction(QIcon(""),tr("正常"),this);
    //normalFrameAction->setShortcuts(Qt::CTRL);
    normalFrameAction->setStatusTip(tr("展示画面大小为正常"));
    hugeFrameAction = new QAction(QIcon(""),tr("放大"),this);
    //hugeFrameAction->setShortcuts(Qt::CTRL);
    hugeFrameAction->setStatusTip(tr("展示画面大小为大"));
    frameSetAction = new QAction(QIcon(""),tr("画面设置"),this);
    //frameSetAction->setShortcuts(Qt::CTRL);
    frameSetAction->setStatusTip(tr("对展示画面进行设置"));
    themeSetAction = new QAction(QIcon(""),tr("主题设置"),this);
    //themeSetAction->setShortcuts(Qt::CTRL);
    themeSetAction->setStatusTip(tr("对主题进行设置"));
    //toolAction = new QAction(QIcon(""),tr("工具"),this);
    //toolAction->setShortcuts(Qt::CTRL);
    //toolAction->setStatusTip(tr("扩展工具"));
    recodScreenAction = new QAction(QIcon(""),tr("录屏"),this);
    //recodScreenAction->setShortcuts(Qt::CTRL);
    recodScreenAction->setStatusTip(tr("对算法展示界面进行录屏"));
    outPutAction = new QAction(QIcon(""),tr("导出"),this);
    //outPutAction->setShortcuts(Qt::CTRL);
    outPutAction->setStatusTip(tr("导出算法展示"));
    helpAction = new QAction(QIcon(""),tr("帮助"),this);
    //helpAction->setShortcuts(Qt::CTRL);
    helpAction->setStatusTip(tr("获得帮助"));
    aboutAction = new QAction(QIcon(""),tr("关于"),this);
    //aboutAction->setShortcuts(Qt::CTRL);
    aboutAction->setStatusTip(tr("关于本软件"));
//配置Action开始
    algoTreeWindowAction->setCheckable(true);
    algoTreeWindowAction->setChecked(true);
    algoDetailsWindowAction->setCheckable(true);
    algoDetailsWindowAction->setChecked(true);
    controlWindowAction->setCheckable(true);
    controlWindowAction->setChecked(true);
    debugWindowAction->setCheckable(true);
    debugWindowAction->setChecked(true);
    stopAction->setEnabled(false);
    finishAction->setEnabled(false);
    rateMenu->setEnabled(false);
    //rateMenu->setDefaultAction(rate_x0_Action);
    rate_x0_Action->setCheckable(true);
    rate_x1_Action->setCheckable(true);
    rate_x1_Action->setChecked(true);
    rate_x2_Action->setCheckable(true);
    rate_x3_Action->setCheckable(true);
    normalFrameAction->setEnabled(false);
    normalFrameAction->setCheckable(true);
    hugeFrameAction->setEnabled(false);
    hugeFrameAction->setCheckable(true);
    frameSetAction->setEnabled(false);
    //recodScreenAction->setEnabled(false);
    //outPutAction->setEnabled(false);
//配置Action结束
//初始化Action结束

//初始化Menu开始
    menu[0] = new QMenu(tr("控制(&C)"), this);
    menu[1] = new QMenu(tr("窗口(&W)"), this);
    menu[2] = new QMenu(tr("画面(&F)"), this);
    menu[3] = new QMenu(tr("工具(&T)"), this);
    menu[4] = new QMenu(tr("帮助(&H)"), this);
//初始化Menu结束
//配置Menu开始
    menu[0]->addAction(startAction);
    menu[0]->addAction(stopAction);
    menu[0]->addAction(finishAction);
    menu[0]->addSeparator();
    menu[0]->addSeparator();
    rateMenu->addAction(rate_x0_Action);
    rateMenu->addAction(rate_x1_Action);
    rateMenu->addAction(rate_x2_Action);
    rateMenu->addAction(rate_x3_Action);
    menu[0]->addMenu(rateMenu);
    menu[0]->addSeparator();

    menu[1]->addAction(algoTreeWindowAction);
    menu[1]->addAction(algoDetailsWindowAction);
    menu[1]->addAction(controlWindowAction);
    menu[1]->addAction(debugWindowAction);

    menu[2]->addAction(normalFrameAction);
    menu[2]->addAction(hugeFrameAction);
    menu[2]->addAction(frameSetAction);
    menu[2]->addAction(themeSetAction);

    menu[3]->addAction(recodScreenAction);
    menu[3]->addAction(outPutAction);

    menu[4]->addAction(helpAction);
    menu[4]->addAction(aboutAction);
//配置Menu结束

//开始添加图标
    QVector <QIcon *> icons;
    QIcon * iconPointer = nullptr;
    QStringList srcList;
    srcList << ":/icon/start.png";
    srcList << ":/icon/stop.png";
    srcList << ":/icon/finish.png";
    srcList << ":/icon/rate1.png";
    srcList << ":/icon/rate0.png";
    srcList << ":/icon/rate1.png";
    srcList << ":/icon/rate2.png";
    srcList << ":/icon/rate3.png";
    srcList << ":/icon/algoTree.png";
    srcList << ":/icon/algoDetail.png";
    srcList << ":/icon/control.png";
    srcList << ":/icon/codeDetail.png";
    srcList << ":/icon/normalFrame.png";
    srcList << ":/icon/hugeFrame.png";
    srcList << ":/icon/frameSet.png";
    srcList << ":/icon/recodScreen.png";
    srcList << ":/icon/output.png";
    srcList << ":/icon/help.png";
    srcList << ":/icon/about.png";
    for(int i = 0;i < srcList.size();i++)
    {
        iconPointer = new QIcon(srcList.at(i));
        icons.append(iconPointer);
    }
    QVector <QIcon *>::iterator iter;
    iter = icons.begin();
    startAction->setIcon(**(iter++));
    stopAction->setIcon(**(iter++));
    finishAction->setIcon(**(iter++));
    rateMenu->setIcon(**(iter++));
    rate_x0_Action->setIcon(**(iter++));//慢速
    rate_x1_Action->setIcon(**(iter++));//正常
    rate_x2_Action->setIcon(**(iter++));//快速
    rate_x3_Action->setIcon(**(iter++));//超快
    //windowsAction->setIcon(QIcon icon(":/icon/.png"));
    algoTreeWindowAction->setIcon(**(iter++));
    algoDetailsWindowAction->setIcon(**(iter++));
    controlWindowAction->setIcon(**(iter++));
    debugWindowAction->setIcon(**(iter++));
    normalFrameAction->setIcon(**(iter++));
    hugeFrameAction->setIcon(**(iter++));
    frameSetAction->setIcon(**(iter++));
    //toolAction->setIcon(QIcon icon(":/icon/.png"));
    recodScreenAction->setIcon(**(iter++));
    outPutAction->setIcon(**(iter++));
    helpAction->setIcon(**(iter++));
    aboutAction->setIcon(**(iter));
//添加图标结束

    for(int i = 0;i<5;i++)//将menu添加到Menubar
        ui->menubar->addMenu(menu[i]);
}

void MainWindow::initStatusBar()
{
    ui->statusbar->addPermanentWidget(version);//组件放状态栏右边部分
}

void MainWindow::initAlgoTree()
{
    QStringList nodeName;
    QStringList leafName;
    QFile file("./data/algoTreeData.xml");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("警告"),tr("初始化AlgoTree数据错误"),QMessageBox::Ok);
        return;
    }
    QXmlStreamReader reader;
    reader.setDevice(&file);
    parsingAlgoTreeXML(reader,nullptr);
    ui->algoTree->insertTopLevelItems(0,rootList);
    file.close();
}

void MainWindow::parsingAlgoTreeXML(QXmlStreamReader &reader, QTreeWidgetItem *node)
{
    while (!reader.atEnd()) {
        if (reader.readNextStartElement() == false)
            return;
        QString nodeName = reader.name().toString();
        if("algo" == nodeName)
        {
            QString algoName = reader.readElementText();
            reader.readNextStartElement();
            int algoType = reader.readElementText().toInt(new bool,10);
            QTreeWidgetItem* newNode = new QTreeWidgetItem(node,QStringList(QString(algoName)),algoType); //添加叶子节点
            node->addChild(newNode);
        }
        else
        {
            if("class" == nodeName)
            {
                QXmlStreamAttributes attributes = reader.attributes();
                reader.readNextStartElement();
                if(reader.isStartElement())
                {
                    QString nodeName = reader.name().toString();
                    if("classname" == nodeName)
                    {

                        QTreeWidgetItem* newNode = nullptr;
                        if(attributes.hasAttribute("root"))
                        {
                            QString algoName = reader.readElementText();
                            newNode = new QTreeWidgetItem(QStringList(QString(algoName)),0); //添加子节点
                            rootList.append(newNode);
                        }
                        else
                        {
                            if(node == nullptr)
                                return;
                            QString algoName = reader.readElementText();
                            newNode = new QTreeWidgetItem(node,QStringList(QString(algoName)),0); //添加子节点
                            node->addChild(newNode);
                        }
                        parsingAlgoTreeXML(reader,newNode);
                    }
                }
            }
            else
                continue;
        }
    }
}

void MainWindow::initExplainDock()
{
    explainUpdater = new AlgoExplain(ui->explainBox);
}

void MainWindow::on_algoTree_itemDoubleClicked(QTreeWidgetItem *node)
{
    SelectedType = (AlgoTypes)node->type();
    QMetaEnum type = QMetaEnum::fromType<data::AlgoTypes>();
    ui->debugBrowser->setText(type.valueToKey(node->type()));
    if(SelectedType == AlgoType::None)
        return;
    AlgoCfgWindow wnd(config,SelectedType);
    wnd.exec();
    //qDebug() << config->configState << endl;
    if(!config->configState)
        return;
    else
        algoDemoStart();
}

void MainWindow::on_algoTree_itemSelectionChanged()
{
    QList<QTreeWidgetItem *> item = ui->algoTree->selectedItems();
    AlgoTypes selectType = (AlgoTypes)item.first()->type();
    explainUpdater->init(selectType);
}

void MainWindow::on_explainBox_currentChanged(int index)
{
    int padding = (ui->explainBox->width() - 15 - fontMetrics().horizontalAdvance(ui->explainBox->itemText(index)))/2;
    setStyleSheet(QString("QToolBox::tab:selected {padding-left: %1px;}").arg(padding));
}

void MainWindow::killComputeThread()
{
    qDebug() << "kkkkkkkkkkkkkiiiiiiiiiiiiiiiiiiilllllllllllllllllllllllllllll" << endl;
    QMessageBox::StandardButton botton = QMessageBox::warning
            (this,tr("警告"),tr("是否退出当前演示？这将销毁本次演示的任何信息。"),QMessageBox::Yes|QMessageBox::No);
    switch(botton)
    {
        case QMessageBox::Yes:{
        structCompute->stopImmediately();
        structCompute = nullptr;
        canva->clearCanva();
        SelectedType = None;
        brush->stopImmediately();
        brush = nullptr;
        UILock(false);
        configClear();
            break;
        }
        case QMessageBox::No:{
                return;
        }
    default :break;
    }
    return;
}
