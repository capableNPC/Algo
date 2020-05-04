#include "algocfgwindow.h"
#include <QDebug>

AlgoCfgWindow::AlgoCfgWindow(Config* cfg,AlgoTypes algoType)
{
    this->config = cfg;
    this->algoType = algoType;
    init();
    //QMetaObject::connectSlotsByName(this);
}

void AlgoCfgWindow::init()
{
    initData();
    createWidgets();
    createLayouts();
    createConnects();
    initWidget();
}

void AlgoCfgWindow::initData()
{
    patternVector.append("([0-9]{0,2};{1}){0,10}");//none
    patternVector.append("([0-9]{0,2};{1}){0,10}");
    patternVector.append("([0-9]{0,2};{1}){0,10}");//只能输入格式 数字（2位）; 最多10个 正则表达式暂时不太明白怎么设置重复
}

void AlgoCfgWindow::createWidgets()
{
    mainLyt = new QVBoxLayout;

    confirmLyt = new QHBoxLayout;
    confirmBtn = new QPushButton(tr("确认"),this);
    confirmBtn->setObjectName("confirmBtn");
    cancelBtn = new QPushButton(tr("取消"),this);
    cancelBtn->setObjectName("cancelBtn");

    inputLyt = new QVBoxLayout;
    inputExplainLbl = new QLabel(this);
    dataEdit = new QLineEdit(this);
    randomBtn = new QPushButton(tr("随机生成"),this);
    randomBtn->setObjectName("randomBtn");
    noDataCheckBox = new QCheckBox(tr("无初始值"),this);
    noDataCheckBox->setObjectName("noDataCheckBox");

    orderLyt = new QHBoxLayout;
    chaosRadio = new QRadioButton(tr("乱序"),this);
    acsRadio = new QRadioButton(tr("升序"),this);
    desRadio = new QRadioButton(tr("降序"),this);
    orderModeGroup = new QGroupBox(tr("序列"),this);

    viewLyt = new QHBoxLayout;
    normalRadio = new QRadioButton(tr("普通视图"),this);
    memoryRadio = new QRadioButton(tr("内存视图"),this);
    viewModeGroup = new QGroupBox(tr("展示模式"),this);

    frameControlLyt = new QHBoxLayout;
    fillCheckBox = new QCheckBox(tr("填充背景"),this);
    frameControlGroup = new QGroupBox(tr("画面设置"),this);
}

void AlgoCfgWindow::createLayouts()
{
    confirmLyt->addWidget(confirmBtn);
    confirmLyt->addWidget(cancelBtn);

    inputLyt->addWidget(inputExplainLbl);
    inputLyt->addWidget(dataEdit);
    inputLyt->addWidget(randomBtn);
    inputLyt->addWidget(noDataCheckBox);

    orderModeGroup->setLayout(orderLyt);
    orderLyt->addWidget(chaosRadio);
    orderLyt->addWidget(acsRadio);
    orderLyt->addWidget(desRadio);
    chaosRadio->setChecked(true);
    acsRadio->setChecked(false);
    acsRadio->setChecked(false);

    viewModeGroup->setLayout(viewLyt);
    viewLyt->addWidget(normalRadio);
    viewLyt->addWidget(memoryRadio);
    normalRadio->setChecked(true);
    memoryRadio->setChecked(false);

    frameControlGroup->setLayout(frameControlLyt);
    frameControlLyt->addWidget(fillCheckBox);
    fillCheckBox->setChecked(true);

    /*
    mainLyt->addLayout(inputLyt);
    mainLyt->addWidget(orderModeGroup);
    mainLyt->addWidget(viewModeGroup);
    mainLyt->addWidget(frameControlGroup);
    mainLyt->addLayout(confirmLyt);
    */
}

void AlgoCfgWindow::createConnects()
{
    connect(randomBtn,&QPushButton::clicked,this,&AlgoCfgWindow::on_randomBtn_clicked);
    connect(confirmBtn,&QPushButton::clicked,this,&AlgoCfgWindow::on_confirmBtn_clicked);
    connect(cancelBtn,&QPushButton::clicked,this,&AlgoCfgWindow::on_cancelBtn_clicked);
    connect(noDataCheckBox,&QCheckBox::stateChanged,this,&AlgoCfgWindow::on_noDataCheckBox_stateChanged);
}

void AlgoCfgWindow::initWidget()
{
    int flag = (int)algoType;
    if(flag >= patternVector.length())
        return;
    pattern = patternVector.at(flag);
    dataRegx.setPattern(pattern);
    dataEdit->setValidator(new QRegExpValidator(dataRegx,this));
    if(algoType == Array)
    {
        mainLyt->addLayout(inputLyt);
        mainLyt->addWidget(orderModeGroup);
        mainLyt->addWidget(viewModeGroup);
        mainLyt->addWidget(frameControlGroup);
        mainLyt->addLayout(confirmLyt);
        this->setLayout(mainLyt);
    }
}

void AlgoCfgWindow::random()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<15; i++)
    {

        int test = qrand()%100;
        config->data << QString::number(test,10);
    }
}

void AlgoCfgWindow::on_randomBtn_clicked()
{
    if(randomBtnSW)
    {
        random();
        QString text;
        foreach(QString str, config->data){
            text = text + str + ";";
        }
        text.chop(1);
        dataEdit->setText(text);
        dataEdit->setEnabled(false);
        randomBtn->setText(tr("修改值"));
        randomBtnSW = false;
    }
    else {
        dataEdit->setEnabled(true);
        randomBtn->setText(tr("随机生成"));
        randomBtnSW = true;
    }
}

void AlgoCfgWindow::on_confirmBtn_clicked()
{
    if(noDataCheckBox->checkState() == Qt::Unchecked)
    {
        if(randomBtnSW)
        {
           QString str = dataEdit->text();
           qDebug() << str << " " << endl;
           config->data.clear();
               if(!str.isEmpty())
               {
                   QString temp = "";
                   int count = 0;
                   do
                   {
                       temp = str.section(";",count,count);
                       config->data << temp;
                        qDebug() << temp << " " << endl;
                       ++count;
                   }while (!temp.isEmpty());//此处会在末尾插入一个无效值0
                   config->data.pop_back();//删除末尾无效值0
               }
        }
        if(fillCheckBox->checkState() == Qt::Checked)
            config->fill = true;
        else
            config->fill = false;
       config->normalView = normalRadio->isChecked();
       if(chaosRadio->isChecked())
           config->order = OrderType::chaos;
       else
       {
           if(acsRadio->isChecked())
               config->order = OrderType::acs;
           else
               config->order = OrderType::des;
       }
    }
    else
    {
        if(noDataCheckBox->checkState() == Qt::Checked)
        {
            config->data.clear();
        }
    }
    confirmBtnClicked = true;
    this->close();
}

void AlgoCfgWindow::on_cancelBtn_clicked()
{
    this->close();
}

void AlgoCfgWindow::on_noDataCheckBox_stateChanged(int state)
{
    if(state == Qt::Unchecked)
    {
        randomBtn->setEnabled(true);
        if(randomBtnSW)
            dataEdit->setEnabled(true);
    }
    else
    {
        if(state == Qt::Checked)
        {
            randomBtn->setEnabled(false);
            dataEdit->setEnabled(false);
        }
    }
}

void AlgoCfgWindow::closeEvent(QCloseEvent* event)
{
    if(confirmBtnClicked)
        config->configState = true;
    else
        config->configState = false;
    event->accept();
}
