/********************************************************************************
** Form generated from reading UI file 'fDrawingPanel.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_fDrawingPanel_H
#define UI_fDrawingPanel_H

#include <QtCore/QVariant>
// #include <QtGui/QAction>
// #include <QtGui/QApplication>
// #include <QtGui/QButtonGroup>
// #include <QtGui/QFrame>
// #include <QtGui/QGridLayout>
// #include <QtGui/QHBoxLayout>
// #include <QtGui/QHeaderView>
// #include <QtGui/QLabel>
// #include <QtGui/QPushButton>
// #include <QtGui/QRadioButton>
// #include <QtGui/QSpacerItem>
// #include <QtGui/QTableWidget>
// #include <QtGui/QVBoxLayout>
// #include <QtGui/QWidget>
// NEW CHANGES
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcombobox.h>
#include <QToolButton>
//#include <QPushButton.h>
#include <qgroupbox.h>
#include <qsize.h>

//#include "CAPTk.h"
#include "CaPTkGUIUtils.h"

QT_BEGIN_NAMESPACE

class Ui_fDrawingPanel
{
public:


  QPushButton * shapeEracerButton;
  QPushButton * clearSelectedLabelButton;
  QPushButton * clearAllLabelButton;

  QPushButton *HelpButton;


  QPushButton * shapeNoneButton;
  QPushButton * shapeFreeHandButton;
  QPushButton *  shapesLineButton;
  QPushButton *  shapesRectangleButton;
  QPushButton *  shapesCircleButton;
  QPushButton *  shapeFillButton;

  QPushButton * UndoButton;
  QComboBox	* sizeComboBox;
  QComboBox	* labelSelectorBox;
  QComboBox *maskOpacitySpinBox;

  QVector<QPushButton*> shapeButtons;

  void setupUi(QWidget *parent)
  {
    
    std::string iconDir = getCaPTkDataDir() + "/icons/";

    iconDir = getCaPTkDataDir() + "/icons/";
    if (!QDir(cbica::normPath(iconDir).c_str()).exists()) // packaged binary
    {
      if (QDir((std::string(PROJECT_SOURCE_DIR) + "/data/icons/").c_str()).exists()) // developer_mode
      {
        iconDir = std::string(PROJECT_SOURCE_DIR) + "/data/icons/";
      }
    }

    QIcon escapeIcon = QIcon((iconDir +"escape.png").c_str());
    QIcon eraseVoxelIcon = QIcon((iconDir + "erase.png").c_str());
    QIcon eraseLabelIcon = QIcon((iconDir + "eraseLabel.png").c_str());
    QIcon eraseAllIcon = QIcon((iconDir + "eraseAll.png").c_str());
    QIcon undoIcon = QIcon((iconDir + "undo.png").c_str());
    QIcon drawIcon = QIcon((iconDir + "draw.png").c_str());
    QIcon lineIcon = QIcon((iconDir + "line.png").c_str());
    QIcon rectangleIcon = QIcon((iconDir + "rectangle.png").c_str());
    QIcon circleIcon = QIcon((iconDir + "circle.png").c_str());
    QIcon fillIcon = QIcon((iconDir + "fill.png").c_str());

    QSize iconSize = QSize(32,32);
    int buttonWidth = QLabel().fontMetrics().width("ButtonSize------------------");

    shapeNoneButton = new QPushButton(parent);
    shapeNoneButton->setText(QString("View Mode"));
    shapeNoneButton->setIcon(QIcon(escapeIcon));

    shapeEracerButton = new QPushButton(parent);
    shapeEracerButton->setIcon(QIcon(eraseVoxelIcon));
    shapeEracerButton->setText(QString("Eraser"));

    shapeFreeHandButton = new QPushButton(parent);
    shapeFreeHandButton->setIcon(drawIcon);
    shapeFreeHandButton->setText("Free-Hand");

    shapesLineButton = new QPushButton(parent);
    shapesLineButton->setIcon(lineIcon);
    shapesLineButton->setText("Line");

    shapesRectangleButton = new QPushButton(parent);
    shapesRectangleButton->setIcon(rectangleIcon);
    shapesRectangleButton->setText("Rectangle");

    shapesCircleButton = new QPushButton(parent);
    shapesCircleButton->setIcon(circleIcon);
    shapesCircleButton->setText("Circle");

    shapeFillButton = new QPushButton(parent);
    shapeFillButton->setIcon(fillIcon);
    //fillButton->setIconSize(iconSize);
    shapeFillButton->setText("Fill");
    shapeFillButton->setToolTip(QString("Fill Selected Region"));
    //fillButton->setFixedWidth(buttonWidth + 25);

    shapeButtons.push_back(shapeNoneButton);
    shapeButtons.push_back(shapeEracerButton);
    shapeButtons.push_back(shapeFreeHandButton);
    shapeButtons.push_back(shapesLineButton);
    shapeButtons.push_back(shapesRectangleButton);
    shapeButtons.push_back(shapesCircleButton);
    shapeButtons.push_back(shapeFillButton);

    for (int i = 0; i < shapeButtons.size(); i++)
    {
      shapeButtons[i]->setIconSize(iconSize);
      shapeButtons[i]->setFixedWidth(buttonWidth);
      shapeButtons[i]->setCheckable(true);
    }

    clearAllLabelButton = new QPushButton(parent);
    clearAllLabelButton->setIcon(QIcon(eraseAllIcon));
    clearAllLabelButton->setIconSize(iconSize);
    clearAllLabelButton->setText(QString("Clear All Labels"));
    clearAllLabelButton->setToolTip(QString("Clear all label from the image"));
    clearAllLabelButton->setFixedWidth(buttonWidth + buttonWidth / 5);

    clearSelectedLabelButton = new QPushButton(parent);
    clearSelectedLabelButton->setIcon(QIcon(eraseLabelIcon));
    clearSelectedLabelButton->setIconSize(iconSize);
    clearSelectedLabelButton->setText(QString("Clear Selected Label"));
    clearSelectedLabelButton->setToolTip(QString("Clear selected label from the image"));
    clearSelectedLabelButton->setFixedWidth(buttonWidth + buttonWidth / 5);



	  UndoButton = new QPushButton(parent);
    UndoButton->setIcon(undoIcon);
    UndoButton->setIconSize(iconSize);
    UndoButton->setText(QString("Undo"));
    UndoButton->setToolTip(QString("Undo previous actions"));
    UndoButton->setFixedWidth(buttonWidth + buttonWidth / 5);


    sizeComboBox = new QComboBox(parent);
    sizeComboBox->setIconSize(iconSize);
    sizeComboBox->setToolTip(QString("Set the size of the brush"));
    sizeComboBox->setFixedWidth(buttonWidth);
    sizeComboBox->insertItem(0, "1x1");
    sizeComboBox->insertItem(1, "3x3");
    sizeComboBox->insertItem(2, "5x5");
    sizeComboBox->insertItem(3, "7x7");
    sizeComboBox->insertItem(4, "9x9");
    fixComboBox(sizeComboBox);

    // multiLabel related stuff starts
    labelSelectorBox = new QComboBox(parent);
    labelSelectorBox->setIconSize(iconSize);
    labelSelectorBox->setToolTip(QString("Select the label to draw"));
    labelSelectorBox->insertItem(0, "1 (Red)");
    labelSelectorBox->insertItem(1, "2 (Green)");
    labelSelectorBox->insertItem(2, "3 (Yellow)");
    labelSelectorBox->insertItem(3, "4 (Blue)");
    labelSelectorBox->insertItem(4, "5 (Magenta)");
    labelSelectorBox->insertItem(5, "6 (Cyan)");
    labelSelectorBox->insertItem(6, "7 (Lt. Red)");
    labelSelectorBox->insertItem(7, "8 (Lt. Green)");
    labelSelectorBox->insertItem(8, "9 (Lt. Blue)");
    labelSelectorBox->setCurrentIndex(0);
    fixComboBox(labelSelectorBox);

    maskOpacitySpinBox = new QComboBox(parent);
    maskOpacitySpinBox->setIconSize(iconSize);
    maskOpacitySpinBox->setToolTip(QString("Select the mask opacity"));
    maskOpacitySpinBox->insertItem(0, "0.0");
    maskOpacitySpinBox->insertItem(1, "0.1");
    maskOpacitySpinBox->insertItem(2, "0.2");
    maskOpacitySpinBox->insertItem(3, "0.3");
    maskOpacitySpinBox->insertItem(4, "0.4");
    maskOpacitySpinBox->insertItem(5, "0.5");
    maskOpacitySpinBox->insertItem(6, "0.6");
    maskOpacitySpinBox->insertItem(7, "0.7");
    maskOpacitySpinBox->insertItem(8, "0.8");
    maskOpacitySpinBox->insertItem(9, "0.9");
    maskOpacitySpinBox->insertItem(10, "1.0");
    maskOpacitySpinBox->setCurrentIndex(10);
    fixComboBox(maskOpacitySpinBox);
    // multiLabel related stuff ends

    //Layout management
    QGroupBox* drawPropertiesGroup= new QGroupBox("Properties");
    QVBoxLayout* drawLayout = new QVBoxLayout();

    drawLayout->addWidget(new QLabel("Label Selector"));
    drawLayout->addWidget(labelSelectorBox);
    drawLayout->addWidget(new QLabel("Marker Size"));
    drawLayout->addWidget(sizeComboBox);
    drawLayout->addWidget(new QLabel("Marker Opacity"));
    drawLayout->addWidget(maskOpacitySpinBox);
    drawPropertiesGroup->setLayout(drawLayout);

    QGroupBox* shapesGroup = new QGroupBox("Drawing Tools");
    QHBoxLayout* shapesLayout = new QHBoxLayout();
    QVBoxLayout* shapesLayout1 = new QVBoxLayout();
    shapesLayout1->addWidget(shapeNoneButton);
    shapesLayout1->addWidget(shapeEracerButton);
    shapesLayout1->addWidget(shapeFreeHandButton);

    QVBoxLayout* shapesLayout2 = new QVBoxLayout();
    shapesLayout2->addWidget(shapesLineButton);
    shapesLayout2->addWidget(shapesRectangleButton);
    shapesLayout2->addWidget(shapesCircleButton);
    shapesLayout2->addWidget(shapeFillButton);

    shapesLayout->addLayout(shapesLayout1);
    shapesLayout->addLayout(shapesLayout2);
    shapesGroup->setLayout(shapesLayout);

    QGroupBox* othersGroup = new QGroupBox("Other");
    QVBoxLayout* othersLayout = new QVBoxLayout();
    othersLayout->addWidget(clearSelectedLabelButton);
    othersLayout->addWidget(clearAllLabelButton);
    othersLayout->addWidget(UndoButton);
  	othersLayout->addStretch();
    othersGroup->setLayout(othersLayout);

    HelpButton = new QPushButton();
    HelpButton->setIcon(QIcon((iconDir + "help.png").c_str()));
    HelpButton->setToolTip("Get Help");
    //HelpButton->setIconSize(QSize(30, 30));
    QVBoxLayout *helpLayout = new QVBoxLayout();
    helpLayout->addWidget(HelpButton);
    helpLayout->addStretch();

	  QHBoxLayout* subLayout = new QHBoxLayout();
	  subLayout->addWidget(shapesGroup);
    subLayout->addWidget(drawPropertiesGroup);
    subLayout->addWidget(othersGroup);
	  subLayout->addStretch();
    subLayout->addLayout(helpLayout);
    QVBoxLayout* mainLayout = new QVBoxLayout(parent);
	  mainLayout->addLayout(subLayout);
	  mainLayout->addStretch();
	  QMetaObject::connectSlotsByName(parent);
  }

};

namespace Ui {
  class fDrawingPanel : public Ui_fDrawingPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_fDrawingPanel_H
