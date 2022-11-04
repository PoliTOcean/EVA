import sys

from PyQt5.QtGui import QColor, QPalette
from PyQt5.QtQml import qmlRegisterType
from PyQt5.QtWidgets import QApplication, QStyleFactory, QWidget
from PyQt5.QtCore import Qt
from MainWindow import MainWindow

import custom_types


def main():
    app = QApplication(sys.argv)
    app.setApplicationName("Monterey")
    app.setApplicationVersion("1.0")
    app.setOrganizationName("PoliTOcean")

    app.setStyle(QStyleFactory.create("Fusion"))
    darkPalette = QPalette()
    darkPalette.setColor(QPalette.Window, QColor(53, 53, 53))
    darkPalette.setColor(QPalette.WindowText, Qt.white)
    darkPalette.setColor(QPalette.Base, QColor(25, 25, 25))
    darkPalette.setColor(QPalette.AlternateBase, QColor(53, 53, 53))
    darkPalette.setColor(QPalette.ToolTipBase, Qt.white)
    darkPalette.setColor(QPalette.ToolTipText, Qt.white)
    darkPalette.setColor(QPalette.Text, Qt.white)
    darkPalette.setColor(QPalette.Button, QColor(53, 53, 53))
    darkPalette.setColor(QPalette.ButtonText, Qt.white)
    darkPalette.setColor(QPalette.BrightText, Qt.red)
    darkPalette.setColor(QPalette.Link, QColor(42, 130, 218))

    darkPalette.setColor(QPalette.Highlight, QColor(42, 130, 218))
    darkPalette.setColor(QPalette.HighlightedText, Qt.black)

    app.setPalette(darkPalette)
    app.setStyleSheet(
        "QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }")

    mainWindow = MainWindow()
    mainWindow.show()

    sys.exit(app.exec())


if __name__ == '__main__':
    main()
