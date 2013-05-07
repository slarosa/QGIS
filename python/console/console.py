# -*- coding:utf-8 -*-
"""
/***************************************************************************
Python Console for QGIS
                             -------------------
begin                : 2012-09-10
copyright            : (C) 2012 by Salvatore Larosa
email                : lrssvtml (at) gmail (dot) com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
Some portions of code were taken from https://code.google.com/p/pydee/
"""

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from qgis.utils import iface
from console_sci import ShellScintilla
from console_output import ShellOutputScintilla
from console_editor import EditorWidget
from console_help import HelpDialog
from console_settings import optionsDialog
from qgis.core import QgsApplication
from qgis.gui import QgsFilterLineEdit

import sys
import os

_console = None

def show_console():
  """ called from QGIS to open the console """
  global _console
  if _console is None:
    parent = iface.mainWindow() if iface else None
    _console = PythonConsole( parent )
    _console.show() # force show even if it was restored as hidden
    # set focus to the console so the user can start typing
    # defer the set focus event so it works also whether the console not visible yet
    QTimer.singleShot(0, _console.activate)
  else:
    _console.setVisible(not _console.isVisible())
    # set focus to the console so the user can start typing
    if _console.isVisible():
      _console.activate()

_old_stdout = sys.stdout
_console_output = None

# hook for python console so all output will be redirected
# and then shown in console
def console_displayhook(obj):
    global _console_output
    _console_output = obj

class PythonConsole(QDockWidget):
    def __init__(self, parent=None):
        QDockWidget.__init__(self, parent)
        self.setObjectName("PythonConsole")
        self.setWindowTitle(QCoreApplication.translate("PythonConsole", "Python Console"))
        #self.setAllowedAreas(Qt.BottomDockWidgetArea)

        self.console = PythonConsoleWidget(self)
        self.setWidget( self.console )
        self.setFocusProxy( self.console )

        # try to restore position from stored main window state
        if iface and not iface.mainWindow().restoreDockWidget(self):
            iface.mainWindow().addDockWidget(Qt.BottomDockWidgetArea, self)

    def activate(self):
        self.activateWindow()
        self.raise_()
        QDockWidget.setFocus(self)

    def closeEvent(self, event):
        self.console.saveSettingsConsole()
        QWidget.closeEvent(self, event)

class PythonConsoleWidget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setWindowTitle(QCoreApplication.translate("PythonConsole", "Python Console"))

        self.options = optionsDialog(self)
        self.helpDlg = HelpDialog(self)

        self.shell = ShellScintilla(self)
        self.setFocusProxy(self.shell)
        self.shellOut = ShellOutputScintilla(self)
        self.tabEditorWidget = EditorWidget(self, pathfile=None)


        ##------------ UI -------------------------------

        self.splitterEditor = QSplitter(self)
        self.splitterEditor.setOrientation(Qt.Horizontal)
        self.splitterEditor.setHandleWidth(6)
        self.splitterEditor.setChildrenCollapsible(True)
        self.splitter = QSplitter(self.splitterEditor)
        self.splitter.setOrientation(Qt.Vertical)
        self.splitter.setHandleWidth(3)
        self.splitter.setChildrenCollapsible(False)
        self.splitter.addWidget(self.shellOut)
        self.splitter.addWidget(self.shell)
        #self.splitterEditor.addWidget(self.tabEditorWidget)

        self.widgetEditor = QWidget(self.splitterEditor)

        # Hide side editor on start up
        self.widgetEditor.hide()

        sizes = self.splitter.sizes()
        self.splitter.setSizes(sizes)

        ##----------------Restore Settings------------------------------------

        self.restoreSettingsConsole()

        ##----------------Toolbar Console-------------------------------------

        ## Action Show Editor
        showEditor = QCoreApplication.translate("PythonConsole", "Show editor")
        self.showEditorButton = QAction(self)
        self.showEditorButton.setEnabled(True)
        self.showEditorButton.setCheckable(True)
        self.showEditorButton.setIcon(QgsApplication.getThemeIcon("console/iconShowEditorConsole.png"))
        self.showEditorButton.setMenuRole(QAction.PreferencesRole)
        self.showEditorButton.setIconVisibleInMenu(True)
        self.showEditorButton.setToolTip(showEditor)
        self.showEditorButton.setText(showEditor)
        ## Action for Clear button
        clearBt = QCoreApplication.translate("PythonConsole", "Clear console")
        self.clearButton = QAction(self)
        self.clearButton.setCheckable(False)
        self.clearButton.setEnabled(True)
        self.clearButton.setIcon(QgsApplication.getThemeIcon("console/iconClearConsole.png"))
        self.clearButton.setMenuRole(QAction.PreferencesRole)
        self.clearButton.setIconVisibleInMenu(True)
        self.clearButton.setToolTip(clearBt)
        self.clearButton.setText(clearBt)
        ## Action for settings
        optionsBt = QCoreApplication.translate("PythonConsole", "Settings")
        self.optionsButton = QAction(self)
        self.optionsButton.setCheckable(False)
        self.optionsButton.setEnabled(True)
        self.optionsButton.setIcon(QgsApplication.getThemeIcon("console/iconSettingsConsole.png"))
        self.optionsButton.setMenuRole(QAction.PreferencesRole)
        self.optionsButton.setIconVisibleInMenu(True)
        self.optionsButton.setToolTip(optionsBt)
        self.optionsButton.setText(optionsBt)
        ## Action menu for class
        actionClassBt = QCoreApplication.translate("PythonConsole", "Import Class")
        self.actionClass = QAction(self)
        self.actionClass.setCheckable(False)
        self.actionClass.setEnabled(True)
        self.actionClass.setIcon(QgsApplication.getThemeIcon("console/iconClassConsole.png"))
        self.actionClass.setMenuRole(QAction.PreferencesRole)
        self.actionClass.setIconVisibleInMenu(True)
        self.actionClass.setToolTip(actionClassBt)
        self.actionClass.setText(actionClassBt)
        ## Import Sextante class
        loadSextanteBt = QCoreApplication.translate("PythonConsole", "Import Sextante class")
        self.loadSextanteButton = QAction(self)
        self.loadSextanteButton.setCheckable(False)
        self.loadSextanteButton.setEnabled(True)
        self.loadSextanteButton.setIcon(QgsApplication.getThemeIcon("console/iconSextanteConsole.png"))
        self.loadSextanteButton.setMenuRole(QAction.PreferencesRole)
        self.loadSextanteButton.setIconVisibleInMenu(True)
        self.loadSextanteButton.setToolTip(loadSextanteBt)
        self.loadSextanteButton.setText(loadSextanteBt)
        ## Import QtCore class
        loadQtCoreBt = QCoreApplication.translate("PythonConsole", "Import PyQt.QtCore class")
        self.loadQtCoreButton = QAction(self)
        self.loadQtCoreButton.setCheckable(False)
        self.loadQtCoreButton.setEnabled(True)
        self.loadQtCoreButton.setIcon(QgsApplication.getThemeIcon("console/iconQtCoreConsole.png"))
        self.loadQtCoreButton.setMenuRole(QAction.PreferencesRole)
        self.loadQtCoreButton.setIconVisibleInMenu(True)
        self.loadQtCoreButton.setToolTip(loadQtCoreBt)
        self.loadQtCoreButton.setText(loadQtCoreBt)
        ## Import QtGui class
        loadQtGuiBt = QCoreApplication.translate("PythonConsole", "Import PyQt.QtGui class")
        self.loadQtGuiButton = QAction(self)
        self.loadQtGuiButton.setCheckable(False)
        self.loadQtGuiButton.setEnabled(True)
        self.loadQtGuiButton.setIcon(QgsApplication.getThemeIcon("console/iconQtGuiConsole.png"))
        self.loadQtGuiButton.setMenuRole(QAction.PreferencesRole)
        self.loadQtGuiButton.setIconVisibleInMenu(True)
        self.loadQtGuiButton.setToolTip(loadQtGuiBt)
        self.loadQtGuiButton.setText(loadQtGuiBt)
        ## Action for Run script
        runBt = QCoreApplication.translate("PythonConsole", "Run command")
        self.runButton = QAction(self)
        self.runButton.setCheckable(False)
        self.runButton.setEnabled(True)
        self.runButton.setIcon(QgsApplication.getThemeIcon("console/iconRunConsole.png"))
        self.runButton.setMenuRole(QAction.PreferencesRole)
        self.runButton.setIconVisibleInMenu(True)
        self.runButton.setToolTip(runBt)
        self.runButton.setText(runBt)
        ## Help action
        helpBt = QCoreApplication.translate("PythonConsole", "Help")
        self.helpButton = QAction(self)
        self.helpButton.setCheckable(False)
        self.helpButton.setEnabled(True)
        self.helpButton.setIcon(QgsApplication.getThemeIcon("console/iconHelpConsole.png"))
        self.helpButton.setMenuRole(QAction.PreferencesRole)
        self.helpButton.setIconVisibleInMenu(True)
        self.helpButton.setToolTip(helpBt)
        self.helpButton.setText(helpBt)

        self.toolBar = QToolBar()
        self.toolBar.setEnabled(True)
        self.toolBar.setFocusPolicy(Qt.NoFocus)
        self.toolBar.setContextMenuPolicy(Qt.DefaultContextMenu)
        self.toolBar.setLayoutDirection(Qt.LeftToRight)
        self.toolBar.setIconSize(QSize(24, 24))
        self.toolBar.setOrientation(Qt.Vertical)
        self.toolBar.setMovable(True)
        self.toolBar.setFloatable(True)
        self.toolBar.addAction(self.clearButton)
        self.toolBar.addAction(self.actionClass)
        self.toolBar.addAction(self.runButton)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.showEditorButton)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.optionsButton)
        self.toolBar.addAction(self.helpButton)

        ## Menu Import Class
        self.classMenu = QMenu()
        self.classMenu.addAction(self.loadSextanteButton)
        self.classMenu.addAction(self.loadQtCoreButton)
        self.classMenu.addAction(self.loadQtGuiButton)
        cM = self.toolBar.widgetForAction(self.actionClass)
        cM.setMenu(self.classMenu)
        cM.setPopupMode(QToolButton.InstantPopup)

        self.widgetButton = QWidget()
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widgetButton.sizePolicy().hasHeightForWidth())
        self.widgetButton.setSizePolicy(sizePolicy)

        self.widgetButtonEditor = QWidget(self.widgetEditor)
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widgetButtonEditor.sizePolicy().hasHeightForWidth())
        self.widgetButtonEditor.setSizePolicy(sizePolicy)

        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.shellOut.sizePolicy().hasHeightForWidth())
        self.shellOut.setSizePolicy(sizePolicy)

        self.shellOut.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.shell.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)

        ##------------ Layout -------------------------------

        self.mainLayout = QGridLayout(self)
        self.mainLayout.setMargin(0)
        self.mainLayout.setSpacing(0)
        self.mainLayout.addWidget(self.widgetButton, 0, 0, 1, 1)
        self.mainLayout.addWidget(self.splitterEditor, 0, 1, 1, 1)

        self.layoutEditor = QGridLayout(self.widgetEditor)
        self.layoutEditor.setMargin(0)
        self.layoutEditor.setSpacing(0)
#         self.layoutEditor.addWidget(self.widgetButtonEditor, 0, 0, 2, 1)
        self.layoutEditor.addWidget(self.tabEditorWidget, 0, 0, 1, 1)
#         self.layoutEditor.addWidget(self.widgetFind, 1, 1, 1, 1)

        self.toolBarLayout = QGridLayout(self.widgetButton)
        self.toolBarLayout.setMargin(0)
        self.toolBarLayout.setSpacing(0)
        self.toolBarLayout.addWidget(self.toolBar)

        ##------------ Add first Tab in Editor -------------------------------

        #self.tabEditorWidget.newTabEditor(tabName='first', filename=None)

        ##------------ Signal -------------------------------

        self.showEditorButton.toggled.connect(self.toggleEditor)
        self.clearButton.triggered.connect(self.shellOut.clearConsole)
        self.optionsButton.triggered.connect(self.openSettings)
        self.loadSextanteButton.triggered.connect(self.sextante)
        self.loadQtCoreButton.triggered.connect(self.qtCore)
        self.loadQtGuiButton.triggered.connect(self.qtGui)
        self.runButton.triggered.connect(self.shell.entered)
        self.helpButton.triggered.connect(self.openHelp)
        self.connect(self.options.buttonBox, SIGNAL("accepted()"),
                     self.prefChanged)

    def sextante(self):
       self.shell.commandConsole('sextante')

    def qtCore(self):
       self.shell.commandConsole('qtCore')

    def qtGui(self):
       self.shell.commandConsole('qtGui')

    def toggleEditor(self, checked):
        self.widgetEditor.show() if checked else self.widgetEditor.hide()
        self.tabEditorWidget.editor.enableToolBarEditor(checked)

    def openHelp(self):
        self.helpDlg.show()
        self.helpDlg.activateWindow()

    def openSettings(self):
        self.options.exec_()

    def prefChanged(self):
        self.shell.settingsShell()
        self.shellOut.refreshLexerProperties()
        self.tabEditorWidget.refreshSettingsEditor()

    def callWidgetMessageBar(self, text):
        self.shellOut.widgetMessageBar(iface, text)

    def saveSettingsConsole(self):
        settings = QSettings()
        #settings.setValue("pythonConsole/geometry", self.saveGeometry())
        settings.setValue("pythonConsole/splitterObj", self.tabEditorWidget.splitterObj.saveState())
        settings.setValue("pythonConsole/splitterEditor", self.splitterEditor.saveState())

        self.shell.writeHistoryFile()

    def restoreSettingsConsole(self):
        # List for tab script
        settings = QSettings()
        storedTabScripts = settings.value("pythonConsole/tabScripts")
        self.tabListScript = storedTabScripts.toList()
        #self.restoreGeometry(settings.value("pythonConsole/geometry").toByteArray())
        self.splitterEditor.restoreState(settings.value("pythonConsole/splitterEditor").toByteArray())
        self.tabEditorWidget.splitterObj.restoreState(settings.value("pythonConsole/splitterObj").toByteArray())

if __name__ == '__main__':
    a = QApplication(sys.argv)
    console = PythonConsoleWidget()
    console.show()
    a.exec_()
