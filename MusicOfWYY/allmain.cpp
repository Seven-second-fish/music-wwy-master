#include "allmain.h"
#include "ui_allmain.h"
#include <QListWidgetItem>
#include <QColor>

AllMain::AllMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllMain),
    player(nullptr)
{
    ui->setupUi(this);

//    this->adjustSize();

//    replaceSlider();

    init();

    //updateSource
//    setupStackedWidget();
//    historyManager = new HistoryManager(stackedWidget);

    //首先去除自带的边框
    this->setWindowFlag(Qt::FramelessWindowHint);

    saveListItemsToIni(); //保存数据到ini文件

    searchData(); //设置查找
    setListT1(); //设置ListT1
    setListT2();
    setListT3();
    setTabWidget(); //设置tabWidget 页
    setPictureWall(); //添加轮播图
    setGallery();  //添加画廊部分
    setButtonMus(); //添加按钮组
    setRankData();//设置排行榜数据
    setRankNew(); //设置新歌榜
   /*歌手模块*/
    setSingerLaug();
    setSingerClass();
    setSingerScreen();
    /*最新音乐模块*/
    setAddWidget();
    setNewMusicButton();
    setNewMusicChooseButton();
    /*左下角模块*/
    setMusicLeft();

}

AllMain::~AllMain()
{
    delete ui;
//    delete historyManager;
    monitor->stopMonitoring();
}

void AllMain::init()
{
    connect(ui->pushButton_min, &QPushButton::clicked, this, &AllMain::btn_bkg_min);
    connect(ui->pushButton_max, &QPushButton::clicked, this, &AllMain::btn_bkg_max);
    connect(ui->pushButton_title_left, &QPushButton::clicked, this, &AllMain::goToPreviousPage);
    connect(ui->pushButton_title_right, &QPushButton::clicked, this, &AllMain::goToNextPage);

    //for music
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop); //循环模式
    player->setPlaylist(playlist);
//    connect(ui->btnPlayPause, &QPushButton::toggled, this, &AllMain::btnPlayPause);
    connect(ui->btnPlayPause, &QPushButton::toggled, [this](bool checked){
        checked?player->play():player->pause();
    });
    //调整状态，滑动时屏蔽player的信号发出，松开时解锁
    connect(ui->horsliderMusic, &QSlider::sliderPressed, [this]() {
        player->blockSignals(true);
    });
    connect(ui->horsliderMusic, &QSlider::sliderReleased, [this]() {
        player->blockSignals(false);
        horsliderMusic_changed(ui->horsliderMusic->value());
    });
    //初始化音乐
    setMusicList();



    //for voice
    volume_slider = this->findChild<QSlider *>("volumeSlider");
    btn_volume = this->findChild<QPushButton *>("btn_volume");
    if (volume_slider) {
        volume_slider->hide();
//        volume_slider->setValue(50);
        updateVolumeUI(50);
    }
    hideSliderTimer = new QTimer(this);
    hideSliderTimer->setInterval(2000);
    hideSliderTimer->setSingleShot(true);
    connect(hideSliderTimer, &QTimer::timeout, this, [this]() {
        volume_slider->hide();
    });
    volume_slider->installEventFilter(this);

    connect(btn_volume, &QPushButton::clicked, [this]() {
        volume_Changed(true);
    });

    connect(volume_slider, &QSlider::valueChanged, [this]() {
        if (!isSystemVolumeChange) {
            int volumeValue = volume_slider->value();
            volume_Changed(volumeValue);
            // 如果是手动调整滑块，更新系统音量
//            setSystemVolume(volumeValue);
        }
    });

    //启用监控系统音量,似乎不生效
//    monitor = new VolumeMonitor(this);
//    monitor->startMonitoring();
//    connect(monitor, &VolumeMonitor::systemVolumeChanged, [this](int newVolume) {
//        isSystemVolumeChange = true;
//        volume_Changed(newVolume);
//        isSystemVolumeChange = false;
//    });

    //for audio

}

//结合customslider类使用,用于实现点击音量进度条某处直接跳转到该位置功能,抛弃该功能
void AllMain::replaceSlider() {
    QSlider *slider = this->findChild<QSlider *>("volumeSlider");
    if (!slider) {
        qWarning() << "QSlider not found!";
        return;
    }

    CustomSlider *customSlider = new CustomSlider(this);
    customSlider->setOrientation(slider->orientation());
    customSlider->setRange(slider->minimum(), slider->maximum());
    customSlider->setValue(slider->value());

    QLayout *layout = slider->parentWidget()->layout();
    if (!layout) {
        qWarning() << "Layout not found!";
        delete slider;
        return;
    }

    QWidget *parentWidget = slider->parentWidget();
    if (!parentWidget->layout()) {
        qWarning() << "Parent widget does not have a layout!";
        return;
    }


    layout->removeWidget(slider);
    delete slider;

    layout->addWidget(customSlider);
    ui->volumeSlider = customSlider;
}


void AllMain::saveListItemsToIni() {
    QStringList setListT1 = {"发现音乐", "播客", "视频", "朋友", "直播", "私人FM"};
    QStringList setListT2_png = {"下载", "最近播放", "云盘", "播客", "收藏"};
    QStringList setListT2_txt = {"本地与下载", "最近播放", "我的音乐云盘", "我的播客", "我的收藏"};
    QStringList setTabWidget = {"个性推荐", "专属定制", "专属定制", "排行榜", "歌手","最新音乐"};
    QStringList setGallery =
    {
         "从《远方》开启保障音乐环游|宝藏雷达",
         "还在听《隐隐约约》吗|时光雷达",
         "今天从《当爱已成往事》听起|私人雷达",
         "孙楠的歌总是令人心动|时光雷达",
         "吉法师带你来听听歌 |qq雷达",
         "从《爱的代价》开启宝藏音乐|时光雷达",
         "你喜欢的韩国音乐|你的雷达",
         "《The end of word》就是那么好听|时光雷达"
    };
    //音乐
//    QStringList setMusic = {
//        "music.mp3"
//    };

    dataSaveControl->saveListItems("setListT1", setListT1, DataSaveControl::ListItems);
    dataSaveControl->saveListItems("setListT2_png", setListT2_png, DataSaveControl::ListItems);
    dataSaveControl->saveListItems("setListT2_txt", setListT2_txt, DataSaveControl::ListItems);
    dataSaveControl->saveListItems("setTabWidget", setTabWidget, DataSaveControl::ListItems);
    dataSaveControl->saveListItems("setGallery", setGallery, DataSaveControl::ListItems);
//    dataSaveControl->saveListItems("setMusic", setMusic, DataSaveControl::ListItems);
}

void AllMain::setupStackedWidget()
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
}

QWidget* AllMain::createPage(int index)
{
    QWidget *page = new QWidget;
    if (index == 0) {
        page->setStyleSheet("background-color: red;");
    } else if (index == 1) {
        page->setStyleSheet("background-color: blue;");
    } else if (index == 2) {
        page->setStyleSheet("background-color: green;");
    }
    return page;
}

void AllMain::navigateToPage(int index)
{
    if (index < 0 || index >= 3) return; // Assuming there are 3 pages
    if (currentPageIndex != index) {
        if (stackedWidget->indexOf(stackedWidget->widget(index)) == -1) {
            // If page not already in the stack, create it
            QWidget *page = createPage(index);
            stackedWidget->addWidget(page);
        }
        currentPageIndex = index;
        historyManager->navigateTo(index);
    }
}

void AllMain::goToPreviousPage()
{
    historyManager->goToPreviousPage();
}

void AllMain::goToNextPage()
{
    historyManager->goToNextPage();
}

//void AllMain::updateUIWithCurrentData() {
//    // 根据 currentIndex 更新 UI
//    // 例如: ui->label->setText(dataList[currentIndex].toString());
//}

//audio
void AllMain::audio_changed()
{

}

//volume
void AllMain::volume_Changed(bool toggleVisibility)
{
    volume_slider = this->findChild<QSlider *>("volumeSlider");
    btn_volume = this->findChild<QPushButton *>("btn_volume");

    if (toggleVisibility && volume_slider) {
        if (volume_slider->isVisible()) {
            volume_slider->hide();
        } else {
            volume_slider->show();
        }
    }

    // 在这种情况下，我们使用滑块的值来更新音量
    if (volume_slider) {
        int volumeValue = volume_slider->value();
        updateVolumeUI(volumeValue);
    }
}

void AllMain::volume_Changed(int volumeValue)
{
    // 更新UI（按钮图标和音量滑块）
    updateVolumeUI(volumeValue);

    // 同步播放器音量
    if (player) {
        player->setVolume(volumeValue);
    }
}

// 更新UI的通用方法
void AllMain::updateVolumeUI(int volumeValue)
{
    if (!volume_slider || !btn_volume) return;

    // 更新音量滑块
    volume_slider->setValue(volumeValue);

    // 确定音量图标
    QString newLevel;
    if (volumeValue == 0) {
        newLevel = "mute";
    } else if (volumeValue > 0 && volumeValue <= 33) {
        newLevel = "level1";
    } else if (volumeValue > 33 && volumeValue <= 66) {
        newLevel = "level2";
    } else {
        newLevel = "level3";
    }

    // 更新按钮图标
    if (btn_volume->property("volumeLevel") != newLevel) {
        btn_volume->setProperty("volumeLevel", newLevel);
        btn_volume->style()->unpolish(btn_volume);
        btn_volume->style()->polish(btn_volume);
    }

    // 强制重绘按钮
    btn_volume->update();
    btn_volume->repaint();
}


void AllMain::searchData()
{
    //加入过滤器
    ui->line_Search->installEventFilter(this);
    ui->line_Search->setMouseTracking(true);
    searchForm = new SearchForm(this); //创建一个新的搜索框
    searchForm->installEventFilter(this);
    searchForm->setMouseTracking(true);
    searchForm->hide();

 //   setAttribute(Qt::WA_StyledBackground); //设置样式表
}

//void AllMain::returnToPreviousLevel() {
//    if (hasPreviousPage()) {
//        // 返回上一个页面的逻辑
//        goToPreviousPage();
//    }
//    updateButtonStates();
//}

//void AllMain::jumpToNextLevel() {
//    if (hasNextPage()) {
//        // 跳转到下一个页面的逻辑
//        goToNextPage();
//    }
//    updateButtonStates();
//}

//// 检查是否有上一个页面
//bool AllMain::hasPreviousPage() {
//    // 返回是否有上一个页面的逻辑
//    return !previousPagesStack.isEmpty();
//}

//// 检查是否有下一个页面
//bool AllMain::hasNextPage() const {
//    // 返回是否有下一个页面的逻辑
//    return !nextPagesStack.isEmpty();
//}

void AllMain::setListT1()
{
    // 取消滚动条
    ui->listT1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QStringList items = dataSaveControl->loadListItems("setListT1", DataSaveControl::ListItems);
    for (int i = 0; i < items.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(ui->listT1);
        item->setText(items[i]);
    }
}

void AllMain::setListT2()
{
    ui->listT2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QStringList items_png = dataSaveControl->loadListItems("setListT2_png", DataSaveControl::ListItems);
    QStringList items_txt = dataSaveControl->loadListItems("setListT2_txt", DataSaveControl::ListItems);
    // 确保两个列表长度相同，以便正确地将图标和文本对应
    int itemCount = qMin(items_png.size(), items_txt.size());
    for (int i = 0; i < itemCount; ++i) {
        QListWidgetItem *item = new QListWidgetItem(ui->listT2);
        item->setIcon(QIcon("./images/" + items_png[i] + ".png"));
        item->setText(items_txt[i]);
        ui->listT2->addItem(item);
    }
}

void AllMain::setListT3()
{
    ui->listT3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListWidgetItem *myLove = new QListWidgetItem(ui->listT3);
    myLove->setIcon(QIcon("./images/心.png"));
    myLove->setText("我喜欢的音乐");

}

void AllMain::setTabWidget()
{
    QStringList items = dataSaveControl->loadListItems("setTabWidget", DataSaveControl::ListItems);
    for (int i = 0; i < items.size(); ++i) {
        ui->tabWidget->setTabText(i,items[i]);
    }
}

void AllMain::setPictureWall()
{
    pictureWidget = new PictureWidget();
    ui->verLout_pic->addWidget(pictureWidget);
}

void AllMain::setGallery()
{
    //初始话数据
    gallerPrivate = new GalleryPrivate();

    QStringList items_Gallery = dataSaveControl->loadListItems("setGallery", DataSaveControl::ListItems);
    QList<GalleryItem * > items;
    for(int i = 0; i < items_Gallery.size(); ++i)
    {
        GalleryItem *item = new GalleryItem();
        item->setPicture(QString("./images/Gallery/%1.png").arg(i + 1)); // 拼接图片路径
        item->setMessage(items_Gallery[i]); // 设置对应的消息
        items.append(item); // 将创建的 GalleryItem 添加到列表中
    }

    // 设置 gallerPrivate 的项资源
    if (!items.isEmpty()) {
        // 获取第一个项的宽度和高度作为参考
        int itemWidth = items.first()->width();
        int itemHeight = items.first()->height();
        gallerPrivate->setItemRes(itemWidth, itemHeight, items);
    }

    ui->horizontalLayout_6->setContentsMargins(0,0,0,0);
    ui->horizontalLayout_6->addWidget(gallerPrivate->getItemViewport());

    this->setStyleSheet("QWidget#customization{border:1px; background:white; border-radius:5px;}");
}

void AllMain::setButtonMus()
{
    pButtonMus = new QButtonGroup(this);
    pButtonMus->addButton(ui->ptn0,0);
    pButtonMus->addButton(ui->ptn1,1);
    pButtonMus->addButton(ui->ptn2,2);
    pButtonMus->addButton(ui->ptn3,3);
    pButtonMus->addButton(ui->ptn4,4);
    pButtonMus->addButton(ui->ptn5,5);
    pButtonMus->addButton(ui->ptn6,6);
    pButtonMus->addButton(ui->ptn7,7);
    pButtonMus->addButton(ui->ptn8,8);
    pButtonMus->addButton(ui->ptn9,9);
    pButtonMus->setExclusive(true);
    pButtonMus->button(0)->setChecked(true);

    connect(pButtonMus, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){
          setSourceMus(id);
    });

}

void AllMain::setSourceMus(int id)
{
    QString str = pButtonMus->button(id)->text();
    ui->ptnChange->setText(str+" >");
    switch (id)
    {
    //0 华语
     case 0:
        {
            QList<QString> arrHuayu;
            for (int i = 0; i<5;i++) {
                arrHuayu.append(QString::asprintf("./images/pictureMusic/huayu%d.png",i));
            }
            QString style = "QWidget#picTitle{border-image:url("+arrHuayu[0]+");}";
            ui->picTitle->setStyleSheet(style);
            style = "QWidget#widMus1{border-image:url("+arrHuayu[1]+");}";
            ui->widMus1->setStyleSheet(style);
            style = "QWidget{border-image:url("+arrHuayu[2]+");}";
            ui->widMus2->setStyleSheet(style);
            style = "QWidget{border-image:url("+arrHuayu[3]+");}";
            ui->widMus3->setStyleSheet(style);
            style = "QWidget{border-image:url("+arrHuayu[4]+");}";
            ui->widMus4->setStyleSheet(style);
            break;
        }
    //流行
    case 1:
    {
        QList<QString> arrLiuxing;
        for (int i = 0; i<5;i++) {
            arrLiuxing.append(QString::asprintf("./images/pictureMusic/liuxing%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrLiuxing[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrLiuxing[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrLiuxing[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrLiuxing[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrLiuxing[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
    //摇滚
    case 2:
    {
        QList<QString> arrYaogun;
        for (int i = 0; i<5;i++) {
            arrYaogun.append(QString::asprintf("./images/pictureMusic/yaogun%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrYaogun[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrYaogun[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrYaogun[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrYaogun[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrYaogun[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //民谣
    case 3:
    {
        QList<QString> arrMinyao;
        for (int i = 0; i<5;i++) {
            arrMinyao.append(QString::asprintf("./images/pictureMusic/minyao%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrMinyao[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrMinyao[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrMinyao[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrMinyao[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrMinyao[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //电子
    case 4:
    {
        QList<QString> arrDianzi;
        for (int i = 0; i<5;i++) {
            arrDianzi.append(QString::asprintf("./images/pictureMusic/dianzi%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrDianzi[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrDianzi[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrDianzi[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrDianzi[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrDianzi[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //另类
    case 5:
    {
        QList<QString> arrLinglei;
        for (int i = 0; i<5;i++) {
            arrLinglei.append(QString::asprintf("./images/pictureMusic/linglei%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrLinglei[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrLinglei[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrLinglei[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrLinglei[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrLinglei[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //轻音乐
    case 6:
    {
        QList<QString> arrQingyinyue;
        for (int i = 0; i<5;i++) {
            arrQingyinyue.append(QString::asprintf("./images/pictureMusic/qingyinyue%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrQingyinyue[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrQingyinyue[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrQingyinyue[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrQingyinyue[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrQingyinyue[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //综艺
    case 7:
    {
        QList<QString> arrZongyi;
        for (int i = 0; i<5;i++) {
            arrZongyi.append(QString::asprintf("./images/pictureMusic/zongyi%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrZongyi[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrZongyi[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrZongyi[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrZongyi[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrZongyi[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //原声
    case 8:
    {
        QList<QString> arrYuansheng;
        for (int i = 0; i<5;i++) {
            arrYuansheng.append(QString::asprintf("./images/pictureMusic/yuansheng%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrYuansheng[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrYuansheng[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrYuansheng[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrYuansheng[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrYuansheng[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
        //ACG
    case 9:
    {
        QList<QString> arrAcg;
        for (int i = 0; i<5;i++) {
            arrAcg.append(QString::asprintf("./images/pictureMusic/Acg%d.png",i));
        }
        QString style = "QWidget#picTitle{border-image:url("+arrAcg[0]+");}";
        ui->picTitle->setStyleSheet(style);
        style = "QWidget#widMus1{border-image:url("+arrAcg[1]+");}";
        ui->widMus1->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrAcg[2]+");}";
        ui->widMus2->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrAcg[3]+");}";
        ui->widMus3->setStyleSheet(style);
        style = "QWidget{border-image:url("+arrAcg[4]+");}";
        ui->widMus4->setStyleSheet(style);
        break;
    }
    default:
        break;
    }
}

void AllMain::setRankData()
{
    //第一个
    QListWidgetItem * newWidget = new QListWidgetItem(ui->listCont);
    RankingItem * item = new  RankingItem();
    newWidget->setBackgroundColor(QColor(249,249,249));
    newWidget->setSizeHint(QSize(item->width(),item->height()));
    item->setNum(1,true);
    item->setStringOrPic("792%");
    item->setMusicName("删了吧");
    item->setMusicAutor("烟(许佳豪)");
    ui->listCont->insertItem(0,newWidget);
    ui->listCont->setItemWidget(newWidget,item);

    //
    QListWidgetItem * newWidget1 = new QListWidgetItem(ui->listCont);
    RankingItem * item1 = new  RankingItem();
    newWidget1->setBackgroundColor(QColor(255,255,255));
    newWidget1->setSizeHint(QSize(item->width(),item->height()));
    item1->setNum(2,true);
    item1->setStringOrPic("127%");
    item1->setMusicName("时间轴");
    item1->setMusicAutor("余佳运");
    ui->listCont->insertItem(1,newWidget1);
    ui->listCont->setItemWidget(newWidget1,item1);

    QListWidgetItem * newWidget2 = new QListWidgetItem(ui->listCont);
    RankingItem * item2 = new  RankingItem();
    newWidget2->setBackgroundColor(QColor(249,249,249));
    newWidget2->setSizeHint(QSize(item->width(),item->height()));
    item2->setNum(3,true);
    item2->setStringOrPic("113%");
    item2->setMusicName("没你也能活下去");
    item2->setMusicAutor("Jony J");
    ui->listCont->insertItem(2,newWidget2);
    ui->listCont->setItemWidget(newWidget2,item2);

    QListWidgetItem * newWidget3 = new QListWidgetItem(ui->listCont);
    RankingItem * item3 = new  RankingItem();
    newWidget3->setBackgroundColor(QColor(255,255,255));
    newWidget3->setSizeHint(QSize(item->width(),item->height()));
    item3->setNum(4,false);
    item3->setStringOrPic("111%");
    item3->setMusicName("都不懂");
    item3->setMusicAutor("吉法师");
    ui->listCont->insertItem(3,newWidget3);
    ui->listCont->setItemWidget(newWidget3,item3);


    QListWidgetItem * newWidget4 = new QListWidgetItem(ui->listCont);
    RankingItem * item4 = new  RankingItem();
    newWidget4->setBackgroundColor(QColor(249,249,249));
    newWidget4->setSizeHint(QSize(item->width(),item->height()));
    item4->setNum(5,false);
    item4->setStringOrPic("88%");
    item4->setMusicName("透明轨迹");
    item4->setMusicAutor("ICY");
    ui->listCont->insertItem(4,newWidget4);
    ui->listCont->setItemWidget(newWidget4,item4);
    //设置第一个选中
    ui->listCont->setCurrentRow(0);

}

void AllMain::setRankNew()
{
    QListWidgetItem * newWidget = new QListWidgetItem(ui->listCont2);
    RankingItem * item = new  RankingItem();
    newWidget->setBackgroundColor(QColor(249,249,249));
    newWidget->setSizeHint(QSize(item->width(),item->height()));
    item->setNum(1,true);
    item->setStringOrPic(0);
    item->setMusicName("删了吧");
    item->setMusicAutor("烟(许佳豪)");
    ui->listCont2->insertItem(0,newWidget);
    ui->listCont2->setItemWidget(newWidget,item);

    //
    QListWidgetItem * newWidget1 = new QListWidgetItem(ui->listCont2);
    RankingItem * item1 = new  RankingItem();
    newWidget1->setBackgroundColor(QColor(255,255,255));
    newWidget1->setSizeHint(QSize(item->width(),item->height()));
    item1->setNum(2,true);
    item1->setStringOrPic(1);
    item1->setMusicName("时间轴");
    item1->setMusicAutor("余佳运");
    ui->listCont2->insertItem(1,newWidget1);
    ui->listCont2->setItemWidget(newWidget1,item1);

    QListWidgetItem * newWidget2 = new QListWidgetItem(ui->listCont2);
    RankingItem * item2 = new  RankingItem();
    newWidget2->setBackgroundColor(QColor(249,249,249));
    newWidget2->setSizeHint(QSize(item->width(),item->height()));
    item2->setNum(3,true);
    item2->setStringOrPic(2);
    item2->setMusicName("没你也能活下去");
    item2->setMusicAutor("Jony J");
    ui->listCont2->insertItem(2,newWidget2);
    ui->listCont2->setItemWidget(newWidget2,item2);

    QListWidgetItem * newWidget3 = new QListWidgetItem(ui->listCont2);
    RankingItem * item3 = new  RankingItem();
    newWidget3->setBackgroundColor(QColor(255,255,255));
    newWidget3->setSizeHint(QSize(item->width(),item->height()));
    item3->setNum(4,false);
    item3->setStringOrPic(2);
    item3->setMusicName("都不懂");
    item3->setMusicAutor("吉法师");
    ui->listCont2->insertItem(3,newWidget3);
    ui->listCont2->setItemWidget(newWidget3,item3);


    QListWidgetItem * newWidget4 = new QListWidgetItem(ui->listCont2);
    RankingItem * item4 = new  RankingItem();
    newWidget4->setBackgroundColor(QColor(249,249,249));
    newWidget4->setSizeHint(QSize(item->width(),item->height()));
    item4->setNum(5,false);
    item4->setStringOrPic(2);
    item4->setMusicName("透明轨迹");
    item4->setMusicAutor("ICY");
    ui->listCont2->insertItem(4,newWidget4);
    ui->listCont2->setItemWidget(newWidget4,item4);
    //设置第一个选中
    ui->listCont2->setCurrentRow(0);
}

void AllMain::setSingerLaug()
{
    pButtonLaug = new QButtonGroup(this);
    pButtonLaug->addButton(ui->ptnAll1,0);
    pButtonLaug->addButton(ui->ptnChinese,1);
    pButtonLaug->addButton(ui->ptnEurope,2);
    pButtonLaug->addButton(ui->ptnJapan,3);
    pButtonLaug->addButton(ui->ptnKorea,4);
    pButtonLaug->addButton(ui->ptnOther1,5);
    pButtonLaug->setExclusive(true);
    pButtonLaug->button(0)->setChecked(true);

    connect(pButtonLaug, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){
          setSingerSourLaug(id);
    });

}

void AllMain::setSingerSourLaug(int id)
{
    //这里可以加载对应图片
    switch (id) {

    default:
        break;
    }
}

void AllMain::setSingerClass()
{
    pButtonClass = new QButtonGroup(this);
    pButtonClass->addButton(ui->ptnAll2,0);
    pButtonClass->addButton(ui->ptnMan,1);
    pButtonClass->addButton(ui->ptnWomen,2);
    pButtonClass->addButton(ui->ptnBank,3);
    pButtonClass->setExclusive(true);
    pButtonClass->button(0)->setChecked(true);

    connect(pButtonClass, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){
          setSingerSourClass(id);
    });
}

void AllMain::setSingerSourClass(int id)
{
    //这里可以加载对应图片
    //这里省略一下
    switch (id) {

    default:
        break;
    }

}

void AllMain::setSingerScreen()
{
    pButtonScreen = new QButtonGroup(this);
    pButtonScreen->addButton(ui->ptnhot,0);
    pButtonScreen->addButton(ui->ptnA,1);
    pButtonScreen->addButton(ui->ptnB,2);
    pButtonScreen->addButton(ui->ptnC,3);
    pButtonScreen->addButton(ui->ptnD,4);
    pButtonScreen->addButton(ui->ptnE,5);
    pButtonScreen->addButton(ui->ptnF,6);
    pButtonScreen->addButton(ui->ptnG,7);
    pButtonScreen->addButton(ui->ptnH,8);
    pButtonScreen->addButton(ui->ptnI,9);
    pButtonScreen->addButton(ui->ptnJ,10);
    pButtonScreen->addButton(ui->ptnK,11);
    pButtonScreen->addButton(ui->ptnL,12);
    pButtonScreen->addButton(ui->ptnM,13);
    pButtonScreen->addButton(ui->ptnN,14);
    pButtonScreen->addButton(ui->ptnO,15);
    pButtonScreen->addButton(ui->ptnP,16);
    pButtonScreen->addButton(ui->ptnQ,17);
    pButtonScreen->addButton(ui->ptnR,18);
    pButtonScreen->addButton(ui->ptnS,19);
    pButtonScreen->addButton(ui->ptnT,20);
    pButtonScreen->addButton(ui->ptnU,21);
    pButtonScreen->addButton(ui->ptnV,22);
    pButtonScreen->addButton(ui->ptnW,23);
    pButtonScreen->addButton(ui->ptnX,24);
    pButtonScreen->addButton(ui->ptnY,25);
    pButtonScreen->addButton(ui->ptnZ,26);
    pButtonScreen->addButton(ui->ptnOH,27);
    pButtonScreen->setExclusive(true);
    pButtonScreen->button(0)->setChecked(true);

    connect(pButtonScreen, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){
          setSingerSourScreen(id);
    });

}

void AllMain::setSingerSourScreen(int id)
{
    //这里可以加载对应图片
    switch (id) {

    default:
        break;
    }

}

void AllMain::setNewMusicButton()
{
    ui->widNewMus->setGeometry(280,10,232,32);
    ui->widNewMus->setStyleSheet("QWidget#widNewMus{background:rgb(255,255,255);border:1px solid rgb(187,187,187);border-radius:16px;}");
    ui->ptnNew->setParent(ui->widNewMus);
    ui->ptnNew->setGeometry(0,1,115,30);
    ui->ptnNew->move(1,1);
    ui->ptnNew->setCheckable(true);
    ui->ptnNew2->setParent(ui->widNewMus);
    ui->ptnNew2->setGeometry(ui->ptnNew->width()+2,1,115,30);
    ui->ptnNew2->move(ui->ptnNew->width()+1,1);
    ui->ptnNew2->setCheckable(true);
    ui->ptnNew->setStyleSheet("QPushButton{color:rgb(55,55,55);border:0px;background:rgb(255,255,255);border-radius:14px;}"
                            "QPushButton:hover{border:0px;background:rgb(244,244,244);border-radius:14px;}"
                            "QPushButton:checked{color:rgb(255,255,255);border:0px;background:rgb(187,187,187);border-radius:14px;}");
    ui->ptnNew2->setStyleSheet("QPushButton{color:rgb(55,55,55);border:0px;background:rgb(255,255,255);border-radius:14px;}"
                            "QPushButton:hover{border:0px;background:rgb(244,244,244);border-radius:14px;}"
                            "QPushButton:checked{color:rgb(255,255,255);border:0px;background:rgb(187,187,187);border-radius:14px;}");
    QButtonGroup * btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->ptnNew,0);
    btnGroup->addButton(ui->ptnNew2,1);
    btnGroup->setExclusive(true);
    btnGroup->button(0)->setChecked(true);

    //连接槽
    connect(btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){
          //这里处理对应界面
        setShowWidget(id);
    });
}

void AllMain::setShowWidget(int id)
{
    currentFlog = id;
    changeChose();

}

void AllMain::setNewMusicChooseButton()
{
    QButtonGroup * btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->ptnMusAll,0);
    btnGroup->addButton(ui->ptnMusChinese,1);
    btnGroup->addButton(ui->ptnMusEurope,2);
    btnGroup->addButton(ui->ptnMusKorea,3);
    btnGroup->addButton(ui->ptnMusJapan,4);
    btnGroup->setExclusive(true);
    btnGroup->button(0)->setChecked(true);

    //连接槽
    connect(btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){
          //这里处理对应界面
          setLanguageChose(id);
    });

}

void AllMain::setAddWidget()
{
   pCourier = new NewCourier;
   pDisMusic = new NewDisc;
   stackedLayout = new QStackedLayout;
   stackedLayout->addWidget(pCourier);
   stackedLayout->addWidget(pDisMusic);
   pCourier->move(0,0);
   ui->verAddWidget->addLayout(stackedLayout);
   stackedLayout->setCurrentIndex(0);

}

void AllMain::setLanguageChose(int id)
{
    currentClass = id;
    changeChose();
}

void AllMain::changeChose()
{
    if(currentFlog == 0)
    {
       pCourier->setChose(currentClass);
       stackedLayout->setCurrentIndex(0);
    }
    else if (currentFlog == 1) {
       pDisMusic->setChose(currentClass);
       stackedLayout->setCurrentIndex(1);
    }
}

void AllMain::setMusicLeft()
{
    MusicForm *musicForm = new MusicForm();
    musicForm->setMusicName("能解答一切的答案");
    musicForm->setMusicAuthor("周深");
    musicForm->setMusicPicture("./images/Messageform/pic.png");
    ui->verticalLayout->addWidget(musicForm);
}

void AllMain::setMusicList()
{
//    QStringList musicList = dataSaveControl.loadListItems("setMusic", DataSaveControl::ListItems);

    QString directoryPath = "./music";
//    QStringList filters; // 如果不需要过滤器，可留空
////    filters << "*.mp3" /*<< "*.txt"*/; // 你可以根据需要添加过滤条件
//    filters << "*.mp3";

    QStringList filters = QStringList() << "*.mp3" ;

    QStringList musicList = dataSaveControl->scanFilesInDirectory(directoryPath, filters);

    connect(player, &QMediaPlayer::positionChanged, [=](qint64 duration){
        if (ui->horsliderMusic->isSliderDown())
        {
            return;
        }
        ui->horsliderMusic->blockSignals(true);
        ui->horsliderMusic->setSliderPosition(int(duration));
        ui->horsliderMusic->blockSignals(false);

        int secs = int(duration) / 1000;
        int min = secs / 60; //取整
        secs = secs % 60; //剩余秒
        positionTime = QString::asprintf("%02d:%02d", min, secs);
        ui->label_time->setText(positionTime);
    });

    connect(player, &QMediaPlayer::durationChanged, [=](qint64 duration){
        ui->horsliderMusic->setMaximum(int(duration));

        int secs = int(duration) / 1000;
        int min = secs / 60; //取整
        secs = secs % 60; //剩余秒
        durationTime = QString::asprintf("%02d:%02d", min, secs);
        ui->label_time_long->setText(durationTime);
    });

    //加载音乐
    for(int i = 0; i < musicList.size(); ++i){
//        playlist->addMedia(QUrl::fromLocalFile("./music/"+musicList[i])); //Add files
//        player->setMedia(QUrl::fromLocalFile(QFileInfo(QString("./music/"+musicList[i])).absoluteFilePath()));
//          loadMusic(player, playlist, "./music/" + musicList[i]);
//        QMediaContent media(QUrl::fromLocalFile("/path/to/your/song.mp3"));
//        player->setMedia(media);

        player->setMedia(QMediaContent(QUrl::fromLocalFile(QFileInfo("./music/"+musicList[i]).absoluteFilePath())));


    }

    playlist->setCurrentIndex(0);
}

//Invocation based on system judgment
void AllMain::loadMusic(QMediaPlayer* player, QMediaPlaylist* playlist, const QString& filePath) {
#ifdef Q_OS_WIN
    playlist->addMedia(QUrl::fromLocalFile(filePath));
#elif defined(Q_OS_LINUX)
    player->setMedia(QUrl::fromLocalFile(QFileInfo(filePath).absoluteFilePath()));
#else
    qDebug() << "Unsupported OS";
#endif
}


void AllMain::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter_mainback(this);
    painter_mainback.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mianwindow/images/mainback.png"));
    ui->pushButton_people->setMask(QRegion(0,0,28,28,QRegion::Ellipse));
}

void AllMain::mousePressEvent(QMouseEvent *event)
{
    //获取title widget 的高度，这里固定为60px
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        last = event->globalPos(); //获取到按压的位置
    }
    QWidget::mousePressEvent(event);
}

void AllMain::mouseMoveEvent(QMouseEvent *event)
{
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        this->move(this->x()+dx,this->y()+dy);
    }
    QWidget::mouseMoveEvent(event);

}

void AllMain::mouseReleaseEvent(QMouseEvent *event)
{
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
    QWidget::mouseReleaseEvent(event);

//    emit btnClickedSig();  // 发出自定义点击信号,用于其他自定义组件
}

//void AllMain::mousePressEvent(QMouseEvent *event)
//{
//    QWidget::mousePressEvent(event);
//}

//void AllMain::mouseReleaseEvent(QMouseEvent *event)
//{
//    QWidget::mouseReleaseEvent(event);
//    if(!isDisable)
//    {
//        setOnoffStatus(!btnState);
//    }
//    emit onoffStatusChanged(btnId,btnState);
//}

bool AllMain::eventFilter(QObject *watched, QEvent *event)
{
    //当点击查询按钮
    if(watched == ui->line_Search)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

            int x = ui->line_Search->x();
            int y = ui->line_Search->y();
            int hight = ui->line_Search->height();
            searchForm->setGeometry(x-45,y+hight+2,searchForm->width(),searchForm->height());
            searchForm->show();
            return true;
        }
        else {
            return false;
        }

    }
    else if (watched == searchForm)
    {
        //当鼠标离开时候，界面隐藏
        if(event->type() == QEvent::Leave)
        {
            searchForm->hide();
            return true;
        }
        else {
            return false;
        }

    }
    else if (watched == ui->volumeSlider) {
        if (event->type() == QEvent::Leave) {
            // 当鼠标离开滑块时启动定时器
            hideSliderTimer->start();
        } else if (event->type() == QEvent::Enter) {
            // 当鼠标再次进入滑块区域时，停止定时器
            hideSliderTimer->stop();
        }
    }

    return QWidget::eventFilter(watched,event);
}

void AllMain::timerEvent(QTimerEvent *event)
{
//    if (event->timerId() == hideSliderTimerId)
//    {
//        QSlider *volume_slider = this->findChild<QSlider *>("volumeSlider");
//        if(volume_slider){
//            volume_slider->hide();
//        }
//        killTimer(hideSliderTimerId); // 一次性操作，关闭定时器
//    }
}

void AllMain::on_pushButton_close_clicked()
{
    this->close();
}

void AllMain::on_pushButton_name_clicked()
{
    if(p_person)
    {
        if(p_person->isHidden())
        {
            p_person->show();
        }
        else {
            p_person->hide();
        }

    }
    else {
        p_person = new personForm(this);
        p_person->setGeometry(538,55,290,400); //这里要调整好
        p_person->raise();  //提示显示层数
        p_person->show();
    }
}

void AllMain::btn_bkg_min()
{
    this->showMinimized(); //最小化
}

void AllMain::btn_bkg_max()
{
// 因为目前没有对应最大窗的ui,就不好实现
//    this->showMaximized(); //最大化
    if (this->isMaximized()) {
        this->showNormal();  // 如果窗口已经最大化，恢复到原始大小
    } else {
        this->showMaximized();  // 否则，最大化窗口
    }
}

/*专属定制中的按钮*/
void AllMain::on_btnPerL_clicked()
{
    int num = gallerPrivate->getPreviousItemIndex();
    gallerPrivate->showImage(num);
}

void AllMain::on_btnPerR_clicked()
{
    int num =gallerPrivate->getNextItemIndex();
    gallerPrivate->showImage(num);
}

void AllMain::on_pushButton_cloth_clicked()
{
    if(changeColor)
    {
        if(changeColor->isHidden())
        {
            changeColor->show();
        }
        else {
            changeColor->hide();
        }

    }
    else {
        changeColor = new ChangeColorForm(this);
        changeColor->setGeometry(578,60,409,317); //这里要调整好
        changeColor->raise();  //提示显示层数
        changeColor->show();
    }


}


/*消息框*/
void AllMain::on_pushButton_message_clicked()
{
    if(pMessageForm)
    {
        if(pMessageForm->isHidden())
        {
            pMessageForm->show();
        }
        else {
            pMessageForm->hide();
        }

    }
    else {
        pMessageForm = new MessageForm(this);
        pMessageForm->setMouseTracking(true);
        pMessageForm->setGeometry(630,60,365,565); //这里要调整好
        pMessageForm->raise();  //提示显示层数
        pMessageForm->show();
    }

}

void AllMain::horsliderMusic_changed(int value)
{
//        player->blockSignals(true);
//        player->setPosition(value);
//        player->blockSignals(false);

    // 在快进或快退时，延迟执行位置设置
    QTimer::singleShot(50, [this, value]() {
        player->setPosition(value);
    });
}

void AllMain::btnPlayPause(bool checked)
{
    if(checked)
    {
        player->play();
//        this->setWindowTitle("能解答一切的答案");
    }
    else {
        player->pause();
    }
}


