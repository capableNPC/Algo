#ifndef ALGOCFGWINDOW_H
#define ALGOCFGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLayout>
#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTime>
#include <QStringList>
#include <QCloseEvent>
#include "datapackage.h"

using namespace data;

class AlgoCfgWindow : public QDialog
{
public:
    AlgoCfgWindow(Config* cfg,AlgoTypes algoType);
    void closeEvent(QCloseEvent *);

private:
    void init();
    void initData();
    void createWidgets();
    void createLayouts();
    void createConnects();
    void initWidget();
    void random();

private slots:
    void on_randomBtn_clicked();
    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();
    void on_noDataCheckBox_stateChanged(int state);//自动关联不上

private:
//<main var>
    Config* config;
    AlgoTypes algoType;
    QRegExp dataRegx;
    QVector<QString> patternVector;
    QString pattern;
    QVBoxLayout * mainLyt;
    bool randomBtnSW = true;
//</main var>

//<base control widget>
    QHBoxLayout * confirmLyt;
    QPushButton * confirmBtn;
    QPushButton * cancelBtn;
    bool confirmBtnClicked = false;
//</base control widget>

//<base data Input widget>
    QVBoxLayout * inputLyt;
    QLabel * inputExplainLbl;
    QLineEdit * dataEdit;
    QPushButton * randomBtn;
    QCheckBox * noDataCheckBox;
//</base data Input widget>

//<data order control widget>
    QHBoxLayout * orderLyt;
    QRadioButton * chaosRadio;
    QRadioButton * acsRadio;
    QRadioButton * desRadio;
    QGroupBox * orderModeGroup;
//</data order control widget>

//<view mode widget>
    QHBoxLayout * viewLyt;
    QRadioButton * normalRadio;
    QRadioButton * memoryRadio;
    QGroupBox * viewModeGroup;
//</view mode widget>

//<frame control widget>
    QHBoxLayout * frameControlLyt;
    QCheckBox * fillCheckBox;
    QGroupBox * frameControlGroup;
//</frame control widget>

};

#endif // ALGOCFGWINDOW_H
