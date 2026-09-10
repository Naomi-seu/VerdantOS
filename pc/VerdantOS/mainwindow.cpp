#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //固定窗口大小
    this->setMaximumSize(1100,750);
    this->setMinimumSize(1100,750);
    this->setWindowTitle("VerdantOS_v1.0 家庭植物管理系统");


    //初始化植物节点树
    initPlantTree();

    //用于设置scroll area的最小高度
    ui->scrollAreaWidgetContents_7->setMinimumHeight(600);

    //切换主视图的按钮组
    QButtonGroup *mainGroup = new QButtonGroup(this);

    mainGroup->addButton(ui->btnPlant);
    mainGroup->addButton(ui->btnDevice);
    mainGroup->addButton(ui->btnSystem);
    mainGroup->setExclusive(true);

    //切换设备管理功能的按钮组

    QButtonGroup *deviceBtnGroup = new QButtonGroup(this);

    deviceBtnGroup->addButton(ui->btnDeviceStatus);
    deviceBtnGroup->addButton(ui->btnCareConfig);
    deviceBtnGroup->addButton(ui->btnAutoCare);
    deviceBtnGroup->addButton(ui->btnManualCare);
    deviceBtnGroup->setExclusive(true);

    //切换系统管理功能的按钮组
    QButtonGroup *systemBtnGroup = new QButtonGroup(this);

    systemBtnGroup->addButton(ui->btnSystemLog);
    systemBtnGroup->addButton(ui->btnPlantLog);
    systemBtnGroup->addButton(ui->btnSystemSettings);
    systemBtnGroup->setExclusive(true);

    //开屏设置
    ui->mainStack->setCurrentWidget(ui->pagePlant);
    ui->btnPlant->setChecked(true);

    //串口设置
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM12");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadWrite);

    //设备管理：设备状态：新增设备功能弹窗
    connect(ui->btnAddDevice,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"新增设备","功能开发中");
    });

    //系统管理：系统日志：在文件夹中显示
    connect(ui->btnShowSystemLogFolder,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"在文件夹中显示","功能开发中");
    });

    //系统管理：植物日志：在文件夹中显示
    connect(ui->btnShowPlantLogFolder,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"在文件夹中显示","功能开发中");
    });

    //系统管理：系统设置：浏览文件目录
    connect(ui->btnSSBrowseLogPath,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"浏览文件目录","功能开发中");
    });

    //系统管理：系统设置：应用系统设置
    connect(ui->btnSSApply,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"应用系统设置","功能开发中");
    });
    //系统管理：系统设置：取消系统设置
    connect(ui->btnSSCancel,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"取消系统设置","功能开发中");
    });

    //打开窗口时发送一个0xaa
    serialPort->write(QByteArray(1, char(0xff)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化植物节点树
void MainWindow::initPlantTree()
{
    // 清空 Designer 中可能存在的默认内容
    ui->treePlants->clear();

    // 北阳台
    QTreeWidgetItem *northBalcony =
        new QTreeWidgetItem(ui->treePlants);
    northBalcony->setText(0, "北阳台");

    QTreeWidgetItem *miniGloxinia =
        new QTreeWidgetItem(northBalcony);
    miniGloxinia->setText(0, "迷你岩桐");

    QTreeWidgetItem *dolphinFlower =
        new QTreeWidgetItem(northBalcony);
    dolphinFlower->setText(0, "海豚花");

    QTreeWidgetItem *gloxinia =
        new QTreeWidgetItem(northBalcony);
    gloxinia->setText(0, "大岩桐");


    // 南阳台
    QTreeWidgetItem *southBalcony =
        new QTreeWidgetItem(ui->treePlants);
    southBalcony->setText(0, "南阳台");

    QTreeWidgetItem *cosmos =
        new QTreeWidgetItem(southBalcony);
    cosmos->setText(0, "波斯菊");

    QTreeWidgetItem *gladiolus =
        new QTreeWidgetItem(southBalcony);
    gladiolus->setText(0, "剑兰");

    QTreeWidgetItem *lemonTree =
        new QTreeWidgetItem(southBalcony);
    lemonTree->setText(0, "柠檬树");


    // 客厅
    QTreeWidgetItem *livingRoom =
        new QTreeWidgetItem(ui->treePlants);
    livingRoom->setText(0, "客厅");

    QTreeWidgetItem *lemonPhilodendron =
        new QTreeWidgetItem(livingRoom);
    lemonPhilodendron->setText(0, "柠檬蔓绿绒");

    QTreeWidgetItem *variegatedPothos =
        new QTreeWidgetItem(livingRoom);
    variegatedPothos->setText(0, "花叶绿萝");


    // 展开所有节点
    ui->treePlants->expandAll();

}
//切换到植物管理主视图
void MainWindow::on_btnPlant_clicked()
{
    ui->mainStack->setCurrentWidget(ui->pagePlant);
}

//切换到设备管理主视图
void MainWindow::on_btnDevice_clicked()
{
    ui->mainStack->setCurrentWidget(ui->pageDevice);
    ui->btnDeviceStatus->setChecked(true);
    ui->deviceStack->setCurrentIndex(0);
}

//切换到系统管理主视图
void MainWindow::on_btnSystem_clicked()
{
    ui->mainStack->setCurrentWidget(ui->pageSystem);
    ui->btnSystemLog->setChecked(true);
    ui->systemStack->setCurrentIndex(0);
}

//系统管理：切换到系统日志
void MainWindow::on_btnSystemLog_clicked()
{
    ui->systemStack->setCurrentWidget(ui->systemLogPage);
}


//系统管理：切换到植物日志
void MainWindow::on_btnPlantLog_clicked()
{
    ui->systemStack->setCurrentWidget(ui->plantLogPage);
}

//系统管理：切换到系统设置
void MainWindow::on_btnSystemSettings_clicked()
{
    ui->systemStack->setCurrentWidget(ui->systemSettingsPage);
}

//设备管理：切换到设备状态
void MainWindow::on_btnDeviceStatus_clicked()
{
    ui->deviceStack->setCurrentWidget(ui->deviceStatusPage);
}


//设备管理：切换到养护配置
void MainWindow::on_btnCareConfig_clicked()
{
    ui->deviceStack->setCurrentWidget(ui->careConfigPage);
}


//设备管理：切换到自动养护
void MainWindow::on_btnAutoCare_clicked()
{
    ui->deviceStack->setCurrentWidget(ui->autoCarePage);
}

//设备管理：切换到手动养护
void MainWindow::on_btnManualCare_clicked()
{
    ui->deviceStack->setCurrentWidget(ui->manualCarePage);
}

//设备管理：养护配置：部署养护配置
void MainWindow::on_btnCCDeploy_clicked()
{

}

