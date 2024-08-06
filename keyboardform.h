#ifndef KEYBOARDFORM_H
#define KEYBOARDFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidgetItem>

#define STYLE_BLACK

namespace Ui {
class KeyboardForm;
}

class KeyboardForm : public QWidget
{
    Q_OBJECT

public:
    explicit KeyboardForm(QWidget *parent = nullptr);
    ~KeyboardForm();

//    void keyPressEvent(QKeyEvent *event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;


private:
    Ui::KeyboardForm *ui;

    QString InputType;
    QLineEdit *CurrentEdit;
    bool IsUpper;
    bool IsShift;
    QString ChineseBuff;
    QStringList Num_Symbol;

    /********初始化函数*********/
    //初始化界面
    void InitForm(void);
    //初始化参数
    void InitParameter(void);
    //初始化图标
    void InitIcon(void);
    //初始化属性
    void InitProperty(void);
    //加载中文字库
    void LoadChineseLib(void);

    /*********功能函数**********/
    //大小写切换
    void CapsLock(void);
    //中英文切换--布局
    void SwitchingChineseAndEnglish(QString Type);
    //设置中英文
    void SetInputType(void);
    //设置Shift
    void SetShiftStatus(void);
    //汉字查询
    void Query_ChineseCharacter(QString pinyin);
    //添加项
    void addOneItem(const QString &text);
    //删除
    void DeleteClick(void);


private slots:
    void Btn_Clicked(void);
    void onItemClicked(QListWidgetItem *item);

private:
    QMap<QString, QList<QPair<QString, QString> > > m_data;

};

#endif // KEYBOARDFORM_H
