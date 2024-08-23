void on_horizontalSlider_music_valueChanged(int value);
void on_pushButton_message_clicked();
#ifndef ALLMAIN_H
#define ALLMAIN_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QButtonGroup>
#include <QStackedLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
//#include <QFile>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>
#include <QStackedWidget>
#include <QSettings>
#include <historymanager.h>
#include "searchform.h"
#include "personform.h"
#include "picturewidget.h"
#include "galleryprivate.h"
#include "galleryitem.h"
#include "rankingitem.h"
#include "newcourier.h"
#include "newdisc.h"
#include "musicform.h"
#include "changecolorform.h"
#include "messageform.h"
#include <QDebug>
#include "datasavecontrol.h"
#include "volumecontrol.h"
#include <QTimer>
#include <QSlider>
#include <customslider.h>
namespace Ui {
class AllMain;
}

class AllMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit AllMain(QWidget *parent = nullptr);
    void initializeConnections(); //Initialize the connection
    void Initializefunction();  //Initialization function
    ~AllMain();
    void searchData();
    void setListT1();  //设置推荐列表
    void setListT2();  //设置我的音乐
    void setListT3();  //设置我喜欢的音乐
    void setTabWidget();  //基本界面
    void setPictureWall(); //添加轮播图
    void setGallery(); //添加画廊部分
    void setButtonMus(); //设置歌单部分按钮
    void setSourceMus(int id); //通过按钮加载对应的数据
    /*排行榜模块*/
    void setRankData(); //设置排行榜数据
    void setRankNew();  //设置新歌榜
    /*歌手模块*/
    void setSingerLaug(); //设置语言
    void setSingerSourLaug(int id); //设置对应图片
    void setSingerClass(); //设置歌手分类
    void setSingerSourClass(int id); //设置对应图片
    void setSingerScreen(); //筛选
    void setSingerSourScreen(int id); //设置对应图片

    /*最新音乐模块*/
    void setNewMusicButton(); //设置新歌速递与新蝶上架模块
    void setShowWidget(int id);  //通过id 显示不同的界面
    void setNewMusicChooseButton(); //设置选项
    void setAddWidget(); //加载对应界面
    void setLanguageChose(int id);
    void changeChose(); //变化对应界面

    /*左下角模块*/
    void setMusicLeft(); //加载左下角模块

    /*初始话音乐*/
    void setMusicList(); //初始化音乐

    // 替换 QSlider 为 CustomSlider
    void replaceSlider();
protected:
    //绘制背景函数
    void paintEvent(QPaintEvent* event);
    //鼠标按下
    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);
    //过滤器函数
    virtual bool eventFilter(QObject *watched, QEvent *event);//过滤器函数

    void timerEvent(QTimerEvent *event);
signals:
    void btnClickedSig();

private slots:
    void on_pushButton_close_clicked();
    void on_pushButton_name_clicked();
//    void on_pushButton_min_clicked();
//    void on_pushButton_max_clicked();
    void btn_bkg_min();
    void btn_bkg_max();
    void on_btnPerL_clicked();
    void on_btnPerR_clicked();
    void on_pushButton_cloth_clicked();
    void on_pushButton_message_clicked();
    void on_horizontalSlider_music_valueChanged(int value);
    void on_pushButton_stop_clicked(bool checked);
    void saveListItemsToIni();

    void goToPreviousPage();
    void goToNextPage();
    void navigateToPage(int index);

    void volume_Changed(bool toggleVisibility);  // change the volume

    void audio_changed();     //change the audio

private:
    Ui::AllMain *ui;
    QPoint last;
    SearchForm * searchForm;  //搜索框
    personForm * p_person = nullptr;    //个人信息按钮
    PictureWidget * pictureWidget;    //图片墙
    GalleryPrivate * gallerPrivate;  //专属定制中的画廊
    QButtonGroup * pButtonMus; //音乐组的
    /*歌手模块*/
    QButtonGroup * pButtonLaug; //语言
    QButtonGroup * pButtonClass; //歌手分类
    QButtonGroup * pButtonScreen;//筛选
    /*最新音乐模块*/
    QStackedLayout *stackedLayout;
    NewCourier * pCourier;
    NewDisc *pDisMusic;
    int currentFlog = 0; //0为新歌速递 1 新蝶上架
    int currentClass= 0; //0为 全部 1为中文 2为欧美 3为韩国 4为日本
    /*换肤的界面*/
    ChangeColorForm * changeColor = nullptr; //换肤
    //个人消息
    MessageForm * pMessageForm = nullptr;

    //播放音乐部分
    QMediaPlayer    *player;//播放器
    QMediaPlaylist  *playlist;//播放列表

    QString  durationTime;//总长度
    QString  positionTime;//当前播放到位置

    DataSaveControl dataSaveControl; //数据保存ini

    //goToPreviousStep
    QStackedWidget *stackedWidget;
    HistoryManager *historyManager;
    int currentPageIndex;
    QWidget* createPage(int index);

    void setupStackedWidget();    //updateSource

    //for volume
    VolumeControl *volumeControl;
    QSlider *volume_slider;
    QPushButton *btn_volume;
    int hideSliderTimerId;  //timerEvent
    int volumeValue;
    QString newLevel;

};

#endif // ALLMAIN_H
