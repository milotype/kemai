#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QSystemTrayIcon>

#include "client/kimaiclient.h"
#include "controller/activitiecontroller.h"
#include "controller/customercontroller.h"
#include "controller/projectcontroller.h"
#include "controller/tagcontroller.h"
#include "updater/kemaiupdater.h"

namespace Ui {
class MainWindow;
}

namespace kemai::app {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void refreshClient();
    void onClientError(const QString& errorMsg);
    void onClientReply(const client::KimaiReply& reply);
    void onActionSettingsTriggered();
    void onActionNewCustomerTriggered();
    void onActionNewProjectTriggered();
    void onActionNewActivityTriggered();
    void onActionCheckUpdateTriggered();
    void onActionOpenHostTriggered();
    void onStackedCurrentChanged(int id);
    void onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void onNewVersionCheckFinished(const updater::VersionDetails& details);
    void onActivityChange(bool started);

private:
    Ui::MainWindow* mUi;
    updater::KemaiUpdater mUpdater;

    // Kimai context
    client::KimaiClient mClient;
    controller::ActivityController mActivityController;
    controller::CustomerController mCustomerController;
    controller::ProjectController mProjectController;
    controller::TagController mTagController;

    // keep stacked widgets ids
    int mActivitySId;
    int mSettingsSId;
    int mCurrentSId = -1;

    // Actions
    QAction* mActQuit        = nullptr;
    QAction* mActSettings    = nullptr;
    QAction* mActNewCustomer = nullptr;
    QAction* mActNewProject  = nullptr;
    QAction* mActNewActivity = nullptr;
    QAction* mActCheckUpdate = nullptr;
    QAction* mActOpenHost    = nullptr;

    // Main menu
    QMenuBar* mMenuBar = nullptr;

    // Tray
    QMenu* mTrayMenu                 = nullptr;
    QSystemTrayIcon* mSystemTrayIcon = nullptr;
};

} // namespace kemai::app
