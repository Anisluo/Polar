#include "showtmpdialog.h"
#include "ui_showtmpdialog.h"
#include<QVBoxLayout>
#include<QHeaderView>

showtmpDialog::showtmpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showtmpDialog)
{
    ui->setupUi(this);
    initWidget();
}

showtmpDialog::~showtmpDialog()
{
    delete ui;
}

void showtmpDialog::initWidget()
{

    QVBoxLayout* layoutMain=new QVBoxLayout(ui->widget);
    tmp_table=new QTableWidget(ui->widget);

    QWidget* panelWnd=new QWidget(ui->widget);

    layoutMain->addWidget(tmp_table,5);
    layoutMain->addWidget(panelWnd,1);

    tmp_table->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    tmp_table->setSelectionMode(QAbstractItemView::SingleSelection); // 单选
    tmp_table->setSelectionBehavior(QAbstractItemView::SelectRows); // 选择整行
    //       tmp_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // 自适应列宽
    tmp_table->verticalHeader()->setVisible(false);
    tmp_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

//确认
void showtmpDialog::on_confirm_btn()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int row = button->property("row").toInt();

        //        tmp_cfg->angleStart=tmp_table->
        tmp_cfg->tempName=tmp_table->item(row,1)->text();
        tmp_cfg->angleStart=tmp_table->item(row,2)->text().toInt();
        tmp_cfg->angleStep=tmp_table->item(row,3)->text().toInt();
        tmp_cfg->angleStop=tmp_table->item(row,4)->text().toInt();
        tmp_cfg->angle_lmax=tmp_table->item(row,5)->text().toInt();
        tmp_cfg->angle_lmin=tmp_table->item(row,6)->text().toInt();
        tmp_cfg->contrast_max=tmp_table->item(row,7)->text().toDouble();
        tmp_cfg->contrast_min=tmp_table->item(row,8)->text().toDouble();
        emit update_tmp_name(tmp_cfg->tempName);
        this->close();//关闭窗口
        qDebug() << "Confirm button clicked in row:" << row;
        // 执行确定按钮的槽函数的逻辑
    }
}

//清空
void showtmpDialog::on_clear_btn()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {

        int row = button->property("row").toInt();
        // 删除前保存按钮的row值
        int currentRow = row;

        tmp_table->removeRow(row);

        // 更新后续按钮的row值
        for (int i = currentRow; i < tmp_table->rowCount(); ++i) {
            QPushButton *nextButton = findChild<QPushButton*>(QString("clearButton_%1").arg(i + 1));
            if (nextButton) {
                nextButton->setProperty("row", i);
            }
        }

        qDebug() << "Clear button clicked in row:" << row;
        // 执行清空按钮的槽函数的逻辑
    }
}

void showtmpDialog::loadConfig(TEMPLATE_CONFIG* tmp)
{
    tmp_cfg=tmp;
}


//更新tmp数据
void showtmpDialog::updatetmp()
{
    QSqlQuery query;
    tmp_table->clear();//清空表
    // 查询所有数据
    if (!query.exec("SELECT * FROM TEMPLATE")) {
        qDebug() << "Error retrieving data:" << query.lastError().text();
        return;
    }

    // 设置表格的列数
    tmp_table->setColumnCount(query.record().count());


    tmp_table->setHorizontalHeaderItem(0, new QTableWidgetItem(QStringLiteral("操作")));
    // 设置表头
    for (int i = 1; i < query.record().count(); ++i) {
        tmp_table->setHorizontalHeaderItem(i, new QTableWidgetItem(query.record().fieldName(i)));
    }

    // 逐行读取数据
    int row = 0;
    while (query.next()) {
        tmp_table->insertRow(row);
        QPushButton *confirm_btn=new QPushButton(QStringLiteral("选中"));
        QPushButton *clear_btn=new QPushButton(QStringLiteral("删除"));
        confirm_btn->setProperty("row",row);
        confirm_btn->setFixedWidth(50);
        clear_btn->setProperty("row",row);
        clear_btn->setFixedWidth(50);
        QWidget* wnd=new QWidget;
        QHBoxLayout* layout=new QHBoxLayout;
        layout->addWidget(confirm_btn);
        layout->addWidget(clear_btn);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0,0,0,0);
        wnd->setLayout(layout);
        tmp_table->setCellWidget(row,0,wnd);

        connect(confirm_btn, SIGNAL(clicked()), this, SLOT(on_confirm_btn()));
        connect(clear_btn, SIGNAL(clicked()), this, SLOT(on_clear_btn()));

        for (int col = 1; col < query.record().count(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            tmp_table->setItem(row, col, item);
        }

        ++row;
    }
}

