from PyQt5.QtGui import QCloseEvent, QImage, QPixmap
from PyQt5.QtWidgets import QApplication, QHBoxLayout, QLCDNumber, QLabel, QMainWindow, QVBoxLayout
from PyQt5.QtCore import QTimer, Qt, pyqtSlot
from Ui_MainWindow import Ui_MainWindow

from QRov import QRovController
from QActivityMonitor import QActivityMonitor
from QLedIndicator import QLedIndicator
from QDepthTape import QDepthTape
from QCompass import QCompass

import numpy as np

from time import strftime

from PyQt5.QtCore import *
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtGui import *
from PyQt5.QtWebEngineWidgets import *

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.controller = QRovController('./config')

        self.addSystemClock()
        self.addActivityMonitor()
        self.addStatusLights()
        self.addSensors()
        self.addRelays()
        self.addDepthTape()
        self.addCompass()

        self.urls = ["https://google.com","http://10.0.0.254:8080"]
        self.urlVal = 0
        self.cameraNames = ["CAM1","CAM2"]
        self.browser = QWebEngineView()
        self.browser.setUrl(QUrl(self.urls[self.urlVal]))
        self.ui.gridLayoutHUD.addWidget(self.browser, 1, 1, 4, 3)  
        self.activityMonitor.displayInfo("Browser Starting")
        

        self.switchButton = QPushButton()
        self.switchButton.setText(self.cameraNames[self.urlVal]) 
        self.ui.gridLayoutHUD.addWidget(self.switchButton,1,3,1,1)
        self.switchButton.clicked.connect(self.button_clicked)

        # Components

        self.ui.graphWidget.setBackground(self.palette().window().color())
        self.ui.graphWidget.ci.layout.setContentsMargins(0, 0, 0, 0)
        self.ui.graphWidget.ci.layout.setSpacing(20)

        width = QApplication.primaryScreen().size().width()
        self.ui.splitterHorizontal.setSizes([int(width/8), int(width*5/8), int(width*2/8)])

    def on_buttonClearLog_clicked(self):
        self.ui.teLog.clear()

    def on_buttonCopyLogToClipboard_clicked(self):
        clipboard = QApplication.clipboard()
        clipboard.setText(self.ui.teLog.toPlainText())

    def setup_plots(self, title, units, position):
        graphColor = self.palette().highlight().color()
        graphColor.setAlpha(90)

        p = self.ui.graphWidget.addPlot(0, position, 1, 1)

        leftAxis = p.getAxis('left')
        leftAxis.setLabel(units=units)
        leftAxis.setPen(self.palette().windowText().color())
        leftAxis.setTextPen(self.palette().windowText().color())

        topAxis = p.getAxis('top')
        topAxis.setPen(self.palette().windowText().color())
        topAxis.setTextPen(self.palette().windowText().color())
        topAxis.setStyle(showValues=False)

        rightAxis = p.getAxis('right')
        rightAxis.setPen(self.palette().windowText().color())
        rightAxis.setTextPen(self.palette().windowText().color())
        rightAxis.setStyle(showValues=False)

        bottomAxis = p.getAxis('bottom')
        bottomAxis.setPen(self.palette().windowText().color())
        bottomAxis.setTextPen(self.palette().windowText().color())
        bottomAxis.setStyle(showValues=False)

        titleColor = self.palette().windowText().color()
        p.setTitle(title, color=titleColor,
                   size='12pt', bold=True)
        p.showAxis('top', True)
        p.showAxis('right', True)
        p.showGrid(x=True, y=True, alpha=0.2)
        p.setMouseEnabled(x=False, y=False)
        p.plot(y=3+np.random.normal(size=50),
               brush=graphColor, fillLevel=0)

    def addSystemClock(self):
        timer = QTimer(self)
        timer.setInterval(1000)
        timer.timeout.connect(self.__update_systemClock)
        timer.start()

    def __update_systemClock(self):
        self.ui.labCurrentTime.setText(strftime("%H"+":"+"%M"+":"+"%S"))

    def addStatusLights(self):
        self.statusLightPower = QLedIndicator("Power")
        self.statusLightRpi = QLedIndicator("RPi")
        self.statusLightJoystick = QLedIndicator("Joystick")
        self.statusLightLights = QLedIndicator("Lights")

        self.controller.joystick.signals.connected.connect(
            self.statusLightJoystick.enable)
        self.controller.joystick.signals.disconnected.connect(
            self.statusLightJoystick.disable)
        self.controller.mqttClient.connected.connect(
            self.statusLightRpi.enable)
        self.controller.mqttClient.disconnected.connect(
            self.statusLightRpi.disable)
        self.controller.powerStateSignals.enabled.connect(
            self.statusLightPower.enable)
        self.controller.powerStateSignals.disabled.connect(
            self.statusLightPower.disable)

        statusGrid = self.ui.groupBoxStatus.layout()
        statusGrid.addWidget(self.statusLightPower.container, 0, 0, 1, 1)
        statusGrid.addWidget(self.statusLightRpi.container, 0, 1, 1, 1)
        statusGrid.addWidget(self.statusLightJoystick.container, 1, 0, 1, 1)
        statusGrid.addWidget(self.statusLightLights.container, 1, 1, 1, 1)

    def addActivityMonitor(self):
        self.activityMonitor = QActivityMonitor(self.ui.teLog)
        self.activityMonitor.displayInfo("GUI started...")

        if self.controller.configured:
            self.activityMonitor.displayInfo(
                "ROV Controller has been configured.")

        self.controller.loggingSignals.info.connect(
            self.activityMonitor.displayInfo)
        self.controller.loggingSignals.warn.connect(
            self.activityMonitor.displayWarn)
        self.controller.loggingSignals.error.connect(
            self.activityMonitor.displayError)

    def addSensors(self):
        if len(self.controller.sensors) > 0:
            vLayout = QVBoxLayout(self.ui.groupBoxSensorReadouts)
            i = 0
            for sensor in self.controller.sensors:
                labelName = QLabel()
                labelName.setText(sensor.name+":")
                labelName.setAlignment(Qt.AlignRight | Qt.AlignVCenter)

                lcd = QLCDNumber()
                lcd.display(sensor.value)
                lcd.setSegmentStyle(QLCDNumber.SegmentStyle.Flat)
                sensor.updated.connect(lcd.display)

                labelUnits = QLabel()
                labelUnits.setText(sensor.units)
                labelUnits.setAlignment(Qt.AlignLeft | Qt.AlignVCenter)

                hLayout = QHBoxLayout(self)
                hLayout.addWidget(labelName)
                hLayout.addWidget(lcd)
                hLayout.addWidget(labelUnits)
                hLayout.setAlignment(hLayout, Qt.AlignHCenter)

                vLayout.addLayout(hLayout)

                self.setup_plots(sensor.name, sensor.units, i)

                i += 1

            self.ui.groupBoxSensorReadouts.setLayout(vLayout)

    def addRelays(self):
        if len(self.controller.relays) > 0:
            for relay in self.controller.relays:
                self.ui.groupBoxRelayButtons.layout().addWidget(relay.button)

    def addDepthTape(self):
        self.depthTape = QDepthTape(maxDepth=10)
        self.controller.sensor('depth').updated.connect(
            self.depthTape.updateDepth)
        self.ui.gridLayoutHUD.addWidget(self.depthTape.container, 1, 0, 4, 1)

    def addCompass(self):
        self.compass = QCompass()
        self.ui.gridLayoutHUD.addWidget(self.compass.container, 0, 0, 1, 4)

    def button_clicked(self):
        self.urlVal = (self.urlVal+1)%2
        self.browser.setUrl(QUrl(self.urls[self.urlVal]))
        self.switchButton.setText(self.cameraNames[self.urlVal]) 

    def closeEvent(self, a0: QCloseEvent) -> None:
        pass

    @pyqtSlot(QImage)
    def setCameraImage(self, img: QImage) -> None:
        self.cameraView.setPixmap(QPixmap.fromImage(img).scaled(
            self.width(), self.height()))