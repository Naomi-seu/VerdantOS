#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnPlant_clicked();

    void on_btnDevice_clicked();

    void on_btnSystem_clicked();

    void on_btnSystemLog_clicked();

    void on_btnPlantLog_clicked();

    void on_btnSystemSettings_clicked();

    void on_btnCCDeploy_clicked();

    void on_btnDeviceStatus_clicked();

    void on_btnCareConfig_clicked();

    void on_btnAutoCare_clicked();

    void on_btnManualCare_clicked();

private:
    Ui::MainWindow *ui;
    void initPlantTree();
};
#endif // MAINWINDOW_H
