# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1280, 752)
        MainWindow.setMinimumSize(QtCore.QSize(1024, 560))
        MainWindow.setMaximumSize(QtCore.QSize(100000, 100000))
        self.centralWidget = QtWidgets.QWidget(MainWindow)
        self.centralWidget.setObjectName("centralWidget")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.centralWidget)
        self.gridLayout_4.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_4.setSpacing(6)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.splitterHorizontal = QtWidgets.QSplitter(self.centralWidget)
        self.splitterHorizontal.setOrientation(QtCore.Qt.Horizontal)
        self.splitterHorizontal.setObjectName("splitterHorizontal")
        self.layoutWidget = QtWidgets.QWidget(self.splitterHorizontal)
        self.layoutWidget.setObjectName("layoutWidget")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.layoutWidget)
        self.verticalLayout_4.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_4.setSpacing(6)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.gridLayout_3 = QtWidgets.QGridLayout()
        self.gridLayout_3.setSpacing(6)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.label_11 = QtWidgets.QLabel(self.layoutWidget)
        font = QtGui.QFont()
        font.setStyleStrategy(QtGui.QFont.PreferAntialias)
        self.label_11.setFont(font)
        self.label_11.setObjectName("label_11")
        self.gridLayout_3.addWidget(self.label_11, 0, 0, 1, 1)
        self.labCurrentTime = QtWidgets.QLabel(self.layoutWidget)
        font = QtGui.QFont()
        font.setStyleStrategy(QtGui.QFont.PreferAntialias)
        self.labCurrentTime.setFont(font)
        self.labCurrentTime.setText("")
        self.labCurrentTime.setObjectName("labCurrentTime")
        self.gridLayout_3.addWidget(self.labCurrentTime, 0, 1, 1, 1)
        self.label_13 = QtWidgets.QLabel(self.layoutWidget)
        font = QtGui.QFont()
        font.setStyleStrategy(QtGui.QFont.PreferAntialias)
        self.label_13.setFont(font)
        self.label_13.setObjectName("label_13")
        self.gridLayout_3.addWidget(self.label_13, 1, 0, 1, 1)
        self.labDiveTime = QtWidgets.QLabel(self.layoutWidget)
        font = QtGui.QFont()
        font.setStyleStrategy(QtGui.QFont.PreferAntialias)
        self.labDiveTime.setFont(font)
        self.labDiveTime.setText("")
        self.labDiveTime.setObjectName("labDiveTime")
        self.gridLayout_3.addWidget(self.labDiveTime, 1, 1, 1, 1)
        self.gridLayout_3.setColumnStretch(0, 1)
        self.gridLayout_3.setColumnStretch(1, 2)
        self.verticalLayout_4.addLayout(self.gridLayout_3)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setSpacing(6)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.groupBoxServoSliders = QtWidgets.QGroupBox(self.layoutWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(2)
        sizePolicy.setHeightForWidth(self.groupBoxServoSliders.sizePolicy().hasHeightForWidth())
        self.groupBoxServoSliders.setSizePolicy(sizePolicy)
        self.groupBoxServoSliders.setObjectName("groupBoxServoSliders")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBoxServoSliders)
        self.horizontalLayout.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout.setSpacing(6)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout_2.addWidget(self.groupBoxServoSliders)
        self.groupBoxRelayButtons = QtWidgets.QGroupBox(self.layoutWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(1)
        sizePolicy.setHeightForWidth(self.groupBoxRelayButtons.sizePolicy().hasHeightForWidth())
        self.groupBoxRelayButtons.setSizePolicy(sizePolicy)
        self.groupBoxRelayButtons.setObjectName("groupBoxRelayButtons")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBoxRelayButtons)
        self.verticalLayout.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout.setSpacing(6)
        self.verticalLayout.setObjectName("verticalLayout")
        self.verticalLayout_2.addWidget(self.groupBoxRelayButtons)
        self.verticalLayout_4.addLayout(self.verticalLayout_2)
        self.layoutWidget1 = QtWidgets.QWidget(self.splitterHorizontal)
        self.layoutWidget1.setObjectName("layoutWidget1")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.layoutWidget1)
        self.verticalLayout_6.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_6.setSpacing(6)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.splitterVertical = QtWidgets.QSplitter(self.layoutWidget1)
        self.splitterVertical.setOrientation(QtCore.Qt.Vertical)
        self.splitterVertical.setObjectName("splitterVertical")
        self.graphWidget = GraphicsLayoutWidget(self.splitterVertical)
        self.graphWidget.setObjectName("graphWidget")
        self.layoutWidget2 = QtWidgets.QWidget(self.splitterVertical)
        self.layoutWidget2.setObjectName("layoutWidget2")
        self.gridLayoutHUD = QtWidgets.QGridLayout(self.layoutWidget2)
        self.gridLayoutHUD.setSizeConstraint(QtWidgets.QLayout.SetDefaultConstraint)
        self.gridLayoutHUD.setContentsMargins(11, 11, 11, 11)
        self.gridLayoutHUD.setSpacing(0)
        self.gridLayoutHUD.setObjectName("gridLayoutHUD")
        self.verticalLayout_6.addWidget(self.splitterVertical)
        self.zoomSlider = QtWidgets.QSlider(self.layoutWidget1)
        self.zoomSlider.setMinimum(0)
        self.zoomSlider.setMaximum(1000)
        self.zoomSlider.setProperty("value", 100)
        self.zoomSlider.setOrientation(QtCore.Qt.Horizontal)
        self.zoomSlider.setTickPosition(QtWidgets.QSlider.NoTicks)
        self.zoomSlider.setObjectName("zoomSlider")
        self.verticalLayout_6.addWidget(self.zoomSlider)
        self.layoutWidget3 = QtWidgets.QWidget(self.splitterHorizontal)
        self.layoutWidget3.setObjectName("layoutWidget3")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.layoutWidget3)
        self.verticalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_5.setSpacing(6)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setSpacing(6)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.groupBoxStatus = QtWidgets.QGroupBox(self.layoutWidget3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBoxStatus.sizePolicy().hasHeightForWidth())
        self.groupBoxStatus.setSizePolicy(sizePolicy)
        self.groupBoxStatus.setMinimumSize(QtCore.QSize(0, 150))
        self.groupBoxStatus.setObjectName("groupBoxStatus")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.groupBoxStatus)
        self.gridLayout_2.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_2.setSpacing(6)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.verticalLayout_3.addWidget(self.groupBoxStatus)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Preferred)
        self.verticalLayout_3.addItem(spacerItem)
        self.groupBoxSensorReadouts = QtWidgets.QGroupBox(self.layoutWidget3)
        self.groupBoxSensorReadouts.setObjectName("groupBoxSensorReadouts")
        self.verticalLayout_3.addWidget(self.groupBoxSensorReadouts)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Preferred)
        self.verticalLayout_3.addItem(spacerItem1)
        self.teLog = QtWidgets.QTextEdit(self.layoutWidget3)
        self.teLog.setLineWrapMode(QtWidgets.QTextEdit.WidgetWidth)
        self.teLog.setReadOnly(True)
        self.teLog.setObjectName("teLog")
        self.verticalLayout_3.addWidget(self.teLog)
        self.verticalLayout_5.addLayout(self.verticalLayout_3)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setSpacing(6)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.buttonClearLog = QtWidgets.QPushButton(self.layoutWidget3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.buttonClearLog.sizePolicy().hasHeightForWidth())
        self.buttonClearLog.setSizePolicy(sizePolicy)
        self.buttonClearLog.setObjectName("buttonClearLog")
        self.horizontalLayout_2.addWidget(self.buttonClearLog)
        self.buttonCopyLogToClipboard = QtWidgets.QPushButton(self.layoutWidget3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.buttonCopyLogToClipboard.sizePolicy().hasHeightForWidth())
        self.buttonCopyLogToClipboard.setSizePolicy(sizePolicy)
        self.buttonCopyLogToClipboard.setFlat(False)
        self.buttonCopyLogToClipboard.setObjectName("buttonCopyLogToClipboard")
        self.horizontalLayout_2.addWidget(self.buttonCopyLogToClipboard)
        self.verticalLayout_5.addLayout(self.horizontalLayout_2)
        self.gridLayout_4.addWidget(self.splitterHorizontal, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralWidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "PolitOcean ROV Controller"))
        self.label_11.setText(_translate("MainWindow", "Time:"))
        self.label_13.setText(_translate("MainWindow", "Dive time:"))
        self.groupBoxServoSliders.setTitle(_translate("MainWindow", "Servos"))
        self.groupBoxRelayButtons.setTitle(_translate("MainWindow", "Relays"))
        self.zoomSlider.setToolTip(_translate("MainWindow", "Zoom the camera feed"))
        self.groupBoxStatus.setTitle(_translate("MainWindow", "Status Lights"))
        self.groupBoxSensorReadouts.setTitle(_translate("MainWindow", "Sensor Readouts"))
        self.buttonClearLog.setToolTip(_translate("MainWindow", "Clears the log from this session of Monterey"))
        self.buttonClearLog.setText(_translate("MainWindow", "Clear Log"))
        self.buttonCopyLogToClipboard.setToolTip(_translate("MainWindow", "Copies the entire log to the clipboard"))
        self.buttonCopyLogToClipboard.setText(_translate("MainWindow", "Copy To Clipboard"))
from pyqtgraph import GraphicsLayoutWidget
