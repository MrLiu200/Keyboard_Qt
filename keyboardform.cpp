#include "keyboardform.h"
#include "ui_keyboardform.h"
#include <QDebug>
#include <QFile>
#include <QScroller>
#include <QKeyEvent>
KeyboardForm::KeyboardForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyboardForm)
{
    ui->setupUi(this);
    LoadChineseLib();
    InitForm();
    InitParameter();

}

KeyboardForm::~KeyboardForm()
{
    delete ui;
}

//void KeyboardForm::keyPressEvent(QKeyEvent *event)
//{

//}

//void KeyboardForm::keyReleaseEvent(QKeyEvent *event)
//{

//}

//void KeyboardForm::mouseMoveEvent(QMouseEvent *event)
//{

//}

//void KeyboardForm::mouseReleaseEvent(QMouseEvent *event)
//{

//}

void KeyboardForm::InitForm()
{
    this->setWindowTitle("自定义键盘 by:卷卷");
//    setWindowFlags(Qt::FramelessWindowHint);//设置窗口背景透明
//    setAttribute(Qt::WA_TranslucentBackground);//设置无边框窗口
    this->setWindowIcon(QIcon(":/Icon/Image/keyboard.png"));

    ui->widget->setStyleSheet("#widget{background-color:rgb(240,135,132);"
                              "border-top-left-radius:15px;border-top-right-radius:15px;"
                              "border-bottom-left-radius:15px;border-bottom-right-radius:15px}");
    InitIcon();
    InitProperty();
    QList<QPushButton *> btns = ui->widget->findChildren<QPushButton *>();
    foreach(QPushButton *button,btns){
        if((button->objectName() != "btn_En") && ((button->objectName() != "btn_Shift")) &&((button->objectName() != "btn_Capslock"))){
            button->setAutoRepeat(true);//设置是否允许自动重复
        }
        button->setFocusPolicy(Qt::NoFocus);
        connect(button,&QPushButton::clicked,this,&KeyboardForm::Btn_Clicked);
    }

    QFont font("楷体",30,QFont::Bold);
    ui->lineEdit->setFont(font);
    ui->btn_En->setText("英");

    /*listWidget*/
//    ui->listWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setFocusPolicy(Qt::NoFocus);
    /* 设置为列表显示模式 */
    ui->listWidget->setViewMode(QListView::ListMode);

    /* 从左往右排列 */
    ui->listWidget->setFlow(QListView::LeftToRight);

    /* 屏蔽水平滑动条 */
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 屏蔽垂直滑动条 */
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 设置为像素滚动 */
    ui->listWidget->setHorizontalScrollMode(QListWidget::ScrollPerPixel);

    /* 设置鼠标左键拖动 */
    QScroller::grabGesture(ui->listWidget, QScroller::LeftMouseButtonGesture);

    /* 设置样式 */
    ui->listWidget->setStyleSheet("                                                                           \
                  QListWidget { outline: none; border:1px solid #00000000; color: black; }    \
                  QListWidget::Item { width: 50px; height: 50px; }                            \
                  QListWidget::Item:hover { background: #4395ff; color: white; }              \
                  QListWidget::item:selected { background: #4395ff; color: black; }           \
                  QListWidget::item:selected:!active { background: #00000000; color: black; } \
                  ");
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));

}

void KeyboardForm::InitParameter()
{
    CurrentEdit = 0;
    InputType = "english";
    IsUpper = false;
    IsShift = false;
    ChineseBuff.clear();
    Num_Symbol.clear();
    Num_Symbol << ")" << "!" << "@" << "#" << "$" << "%" << "^" << "&" << "*" << "(" ;
}

void KeyboardForm::InitIcon()
{
#ifdef STYLE_BLACK
    ui->btn_Capslock->setIcon(QIcon(":/Icon/Image/black/capslock.png"));
    ui->btn_Space->setIcon(QIcon(":/Icon/Image/black/spacebar_black.png"));
    ui->btn_Delete->setIcon(QIcon(":/Icon/Image/black/backspace_black.png"));
    ui->btn_Enter->setIcon(QIcon(":/Icon/Image/black/enter_black.png"));
#elif STYLE_WHITE
    ui->btn_Capslock->setIcon(QIcon(":/Icon/Image/white/caplock.png"));
    ui->btn_Space->setIcon(QIcon(":/Icon/Image/white/space.png"));
    ui->btn_Delete->setIcon(QIcon(":/Icon/Image/white/backspace.png"));
    ui->btn_Enter->setIcon(QIcon(":/Icon/Image/white/enter.png"));
#endif
}

void KeyboardForm::InitProperty()
{
    ui->btn_0->setProperty("btn_Num",true);
    ui->btn_1->setProperty("btn_Num",true);
    ui->btn_2->setProperty("btn_Num",true);
    ui->btn_3->setProperty("btn_Num",true);
    ui->btn_4->setProperty("btn_Num",true);
    ui->btn_5->setProperty("btn_Num",true);
    ui->btn_6->setProperty("btn_Num",true);
    ui->btn_7->setProperty("btn_Num",true);
    ui->btn_8->setProperty("btn_Num",true);
    ui->btn_9->setProperty("btn_Num",true);

    ui->btn_A->setProperty("btn_Letter",true);
    ui->btn_B->setProperty("btn_Letter",true);
    ui->btn_C->setProperty("btn_Letter",true);
    ui->btn_D->setProperty("btn_Letter",true);
    ui->btn_E->setProperty("btn_Letter",true);
    ui->btn_F->setProperty("btn_Letter",true);
    ui->btn_G->setProperty("btn_Letter",true);
    ui->btn_H->setProperty("btn_Letter",true);
    ui->btn_I->setProperty("btn_Letter",true);
    ui->btn_J->setProperty("btn_Letter",true);
    ui->btn_K->setProperty("btn_Letter",true);
    ui->btn_L->setProperty("btn_Letter",true);
    ui->btn_M->setProperty("btn_Letter",true);
    ui->btn_N->setProperty("btn_Letter",true);
    ui->btn_O->setProperty("btn_Letter",true);
    ui->btn_P->setProperty("btn_Letter",true);
    ui->btn_Q->setProperty("btn_Letter",true);
    ui->btn_R->setProperty("btn_Letter",true);
    ui->btn_S->setProperty("btn_Letter",true);
    ui->btn_T->setProperty("btn_Letter",true);
    ui->btn_U->setProperty("btn_Letter",true);
    ui->btn_V->setProperty("btn_Letter",true);
    ui->btn_W->setProperty("btn_Letter",true);
    ui->btn_X->setProperty("btn_Letter",true);
    ui->btn_Y->setProperty("btn_Letter",true);
    ui->btn_Z->setProperty("btn_Letter",true);

    ui->btn_Minus->setProperty("btn_Symbol",true);
    ui->btn_Add->setProperty("btn_Symbol",true);
    ui->btn_Kuo_L->setProperty("btn_Symbol",true);
    ui->btn_Kuo_R->setProperty("btn_Symbol",true);
    ui->btn_Semicolon->setProperty("btn_Symbol",true);
    ui->btn_Yinhao->setProperty("btn_Symbol",true);
    ui->btn_Comma->setProperty("btn_Symbol",true);
    ui->btn_Question->setProperty("btn_Symbol",true);
    ui->btn_Period->setProperty("btn_Symbol",true);

    ui->btn_Delete->setProperty("btn_Tool",true);
    ui->btn_Capslock->setProperty("btn_Tool",true);
    ui->btn_Shift->setProperty("btn_Tool",true);
    ui->btn_Space->setProperty("btn_Tool",true);
    ui->btn_Enter->setProperty("btn_Tool",true);

    ui->btn_En->setProperty("btn_En",true);

}

void KeyboardForm::LoadChineseLib()
{
    QFile file(":/Chineselib/chineselib/GoogleChineselib.txt");
    if (! file.open(QIODevice::ReadOnly)) {
        qDebug() << "Open pinyin file failed!" << file.fileName();
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-16"); // change the file codec to UTF-16.

    QStringList lines = in.readAll().split("\n");

    for (QString each : lines) {
        QRegExp re(R"RX((\S+).((?:-?\d+)(?:\.\d+)).((?:-?\d+)(?:\.\d+)?).(.*))RX");
        int pos = 0;

        bool isMatching = false;
        while ((pos = re.indexIn(each, pos)) != -1) {
            pos += re.matchedLength();
            if (re.captureCount() != 4)
                continue;

            isMatching = true;
            QString hanzi = re.cap(1); // 汉字
            QString weight = re.cap(2); // 权重
            QString tmp = re.cap(3); // 未知
            QString pinyin = re.cap(4); // 拼音(可能是词组)

            QStringList strList = pinyin.split(" ");
            QString abb;
            for (int i = 0; i < strList.count(); i++) {
                /* 获得拼音词组的首字母(用于缩写匹配) */
                abb += strList.at(i).left(1);
            }

            QList<QPair<QString, QString> > &list = m_data[pinyin.left(1)];
            if (strList.count() > 1) {
                /* 将'拼音(缩写)'和'词组'写入匹配容器 */
                list.append(qMakePair(abb, hanzi));
            }
            /* 将'拼音(全拼)'和'词组'写入匹配容器 */
            list.append(qMakePair(pinyin.remove(" "), hanzi));
        }

        if (!isMatching)
            qDebug() << each;
    }

    file.close();
}

void KeyboardForm::CapsLock()
{//问题： 如果是中文的时候怎么办呢？也是直接切换吗
    if(IsUpper){//如果此时是大写，那么切换回去
        IsUpper = false;
        ui->btn_Capslock->setIcon(QIcon(":/Icon/Image/black/capslock.png"));
        SwitchingChineseAndEnglish(InputType);
    }else{//如果是小写，变换为大写
        ui->btn_A->setText("A");
        ui->btn_B->setText("B");
        ui->btn_C->setText("C");
        ui->btn_D->setText("D");
        ui->btn_E->setText("E");
        ui->btn_F->setText("F");
        ui->btn_G->setText("G");
        ui->btn_H->setText("H");
        ui->btn_I->setText("I");
        ui->btn_J->setText("J");
        ui->btn_K->setText("K");
        ui->btn_L->setText("L");
        ui->btn_M->setText("M");
        ui->btn_N->setText("N");
        ui->btn_O->setText("O");
        ui->btn_P->setText("P");
        ui->btn_Q->setText("Q");
        ui->btn_R->setText("R");
        ui->btn_S->setText("S");
        ui->btn_T->setText("T");
        ui->btn_U->setText("U");
        ui->btn_V->setText("V");
        ui->btn_W->setText("W");
        ui->btn_X->setText("X");
        ui->btn_Y->setText("Y");
        ui->btn_Z->setText("Z");
        //设置 CapsLock 按键为按下状态
        IsUpper = true;
        ui->btn_Capslock->setIcon(QIcon(":/Icon/Image/black/capslock_fill.png"));
    }
}

void KeyboardForm::SwitchingChineseAndEnglish(QString Type)
{
    if(Type == "english"){
        ui->btn_En->setText("英");
        ui->btn_A->setText("a");
        ui->btn_B->setText("b");
        ui->btn_C->setText("c");
        ui->btn_D->setText("d");
        ui->btn_E->setText("e");
        ui->btn_F->setText("f");
        ui->btn_G->setText("g");
        ui->btn_H->setText("h");
        ui->btn_I->setText("i");
        ui->btn_J->setText("j");
        ui->btn_K->setText("k");
        ui->btn_L->setText("l");
        ui->btn_M->setText("m");
        ui->btn_N->setText("n");
        ui->btn_O->setText("o");
        ui->btn_P->setText("p");
        ui->btn_Q->setText("q");
        ui->btn_R->setText("r");
        ui->btn_S->setText("s");
        ui->btn_T->setText("t");
        ui->btn_U->setText("u");
        ui->btn_V->setText("v");
        ui->btn_W->setText("w");
        ui->btn_X->setText("x");
        ui->btn_Y->setText("y");
        ui->btn_Z->setText("z");
    }else if(Type == "chinese"){
        ui->btn_En->setText("中");
        ui->btn_A->setText("A");
        ui->btn_B->setText("B");
        ui->btn_C->setText("C");
        ui->btn_D->setText("D");
        ui->btn_E->setText("E");
        ui->btn_F->setText("F");
        ui->btn_G->setText("G");
        ui->btn_H->setText("H");
        ui->btn_I->setText("I");
        ui->btn_J->setText("J");
        ui->btn_K->setText("K");
        ui->btn_L->setText("L");
        ui->btn_M->setText("M");
        ui->btn_N->setText("N");
        ui->btn_O->setText("O");
        ui->btn_P->setText("P");
        ui->btn_Q->setText("Q");
        ui->btn_R->setText("R");
        ui->btn_S->setText("S");
        ui->btn_T->setText("T");
        ui->btn_U->setText("U");
        ui->btn_V->setText("V");
        ui->btn_W->setText("W");
        ui->btn_X->setText("X");
        ui->btn_Y->setText("Y");
        ui->btn_Z->setText("Z");
    }
}

void KeyboardForm::SetInputType()
{
    if(InputType == "english"){
        InputType = "chinese";
    }else if(InputType == "chinese"){
        InputType = "english";
    }
    ChineseBuff.clear();
    Query_ChineseCharacter(ChineseBuff);
}

void KeyboardForm::SetShiftStatus()
{
    if(IsShift){
        IsShift = false;
        ui->btn_Shift->setStyleSheet("");
    }else if(!IsShift){
        IsShift = true;
        ui->btn_Shift->setStyleSheet("background-color:rgb(115,251,253)");

    }
}

void KeyboardForm::Query_ChineseCharacter(QString pinyin)
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->takeItem(i);
        delete item;
        item = NULL;
    }

    ui->listWidget->clear();

    addOneItem(pinyin);

    if (! m_data.contains(pinyin.left(1))) {
        return;
    }

    /* 通过获取首字母索引词库内容，用于加快匹配词(组)。 */
    const QList<QPair<QString, QString> > &tmp = m_data[pinyin.left(1)];
    for (int i = 0; i < tmp.count(); i++) {
        const QPair<QString, QString> &each = tmp.at(i);
        /* 模糊匹配 */
        if (each.first.left(pinyin.count()) != pinyin)
            continue;

        /* 添加到候选栏, 并限制数量 */
        if (ui->listWidget->count() <= 30) {
            addOneItem(each.second);
        }
        else {
            break;
        }
    }
}

void KeyboardForm::addOneItem(const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(text, ui->listWidget);
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    font.setWeight(50);
    item->setFont(font);

    /* 设置文字居中 */
    item->setTextAlignment(Qt::AlignCenter);
    bool isChinese = QRegExp("^[\u4E00-\u9FA5]+").indexIn(text.left(1)) != -1;

    int width = font.pointSize();
    if (isChinese)
        width += text.count()*font.pointSize()*1.5;
    else
        width += text.count()*font.pointSize()*2/3;

    item->setSizeHint(QSize(width, 50));
    ui->listWidget->addItem(item);
}

void KeyboardForm::DeleteClick()
{//先判断汉字区是否有字
    if(!ChineseBuff.isEmpty()){
        ChineseBuff.chop(1);
        Query_ChineseCharacter(ChineseBuff);
    }else{
        QString text = ui->lineEdit->text();
        int len = text.length();
        if(len != 0){
            ui->lineEdit->setText(text.left(len - 1));
        }
    }
}


void KeyboardForm::Btn_Clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
//    qDebug()<<"name = " << objectName;

    if(objectName == "btn_En"){//中英文切换
        SetInputType();
        SwitchingChineseAndEnglish(InputType);
    }else if(objectName == "btn_Capslock"){//大小写切换
        CapsLock();
    }else if(objectName == "btn_Enter"){//回车
        /*回车键有什么用处，只有中文的时候有用处吧？回车就是选好了以后直接回车*/
        if(!ChineseBuff.isEmpty()){
            QString CurrentText = ui->lineEdit->text();
            CurrentText += ChineseBuff;
            ui->lineEdit->setText(CurrentText);
            ChineseBuff.clear();
            Query_ChineseCharacter(ChineseBuff);
        }
    }else if(objectName == "btn_Shift"){//shift
        SetShiftStatus();
    }else if(objectName == "btn_Delete"){//Backspace
        DeleteClick();
    }else if(objectName == "btn_Space"){//Space
        QString CurrentText = ui->lineEdit->text();
        CurrentText += " ";
        ui->lineEdit->setText(CurrentText);
    }else{//数字、字母、符号
        QString Text = btn->text();
        QString CurrentText = ui->lineEdit->text();
        if(btn->property("btn_Letter").toBool()){//字母
            if(IsUpper){//如果开了大写直接返回大写
                CurrentText += Text;
                ui->lineEdit->setText(CurrentText);
            }else{
                if(InputType == "english"){

                    CurrentText += Text;
                    ui->lineEdit->setText(CurrentText);
                }else if(InputType == "chinese"){
                    //中文模式下
                    ChineseBuff.append(Text.toLower());
                    Query_ChineseCharacter(ChineseBuff);
                }
            }
        }else if(btn->property("btn_Num").toBool()){//数字
            Text = Text.mid(0,1);
            if(IsShift){
                int value = Text.toInt();
                CurrentText += Num_Symbol.at(value);
                ui->lineEdit->setText(CurrentText);
            }else{
                CurrentText += Text;
                ui->lineEdit->setText(CurrentText);
            }
        }else if(btn->property("btn_Symbol").toBool()){//符号
            if(IsShift){
                Text = Text.mid(Text.length()-1,1);
                CurrentText += Text;
                ui->lineEdit->setText(CurrentText);
            }else{
                Text = Text.mid(0,1);
                CurrentText += Text;
                ui->lineEdit->setText(CurrentText);
            }
        }
    }
}

void KeyboardForm::onItemClicked(QListWidgetItem *item)
{
    QString Text = item->text();
    QString CurrentText = ui->lineEdit->text();
    CurrentText += Text;
    ui->lineEdit->setText(CurrentText);
    ChineseBuff.clear();//清空buffer
    ui->listWidget->clear();
}

