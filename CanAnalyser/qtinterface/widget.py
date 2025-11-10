# This Python file uses the following encoding: utf-8
import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QLabel,
    QPushButton, QComboBox, QTextEdit, QStackedWidget
)
from PySide6.QtCore import Qt  # Ajout de cette ligne pour Qt.AlignCenter
from PySide6.QtGui import QPixmap  # Pour afficher une image
from PySide6.QtSerialPort import QSerialPort, QSerialPortInfo


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Application Port Série")
        self.showMaximized()  # Maximiser la fenêtre à l'ouverture

        # Configuration du QStackedWidget
        self.pages = QStackedWidget()

        # Ajouter les pages
        self.page1 = SerialConfigPage(self)
        self.page2 = InteractionPage(self)
        self.pages.addWidget(self.page1)
        self.pages.addWidget(self.page2)

        # Layout principal
        main_layout = QVBoxLayout()

        # Ajouter le logo et le titre dans une seule ligne (QHBoxLayout)
        header_layout = QHBoxLayout()

        # Ajouter le logo ISI (déplacer en haut à gauche et redimensionner)
        self.logo_label = QLabel()
        pixmap = QPixmap("D:\CanAnalyser\qtinterface\isi.png")  # Remplacez par le chemin de votre logo
        pixmap = pixmap.scaled(50, 50, Qt.KeepAspectRatio)  # Redimensionner l'image
        self.logo_label.setPixmap(pixmap)
        self.logo_label.setAlignment(Qt.AlignLeft | Qt.AlignVCenter)  # Positionner en haut à gauche

        # Ajouter le titre du dashboard
        self.title_label = QLabel("CANAnalyser")
        self.title_label.setAlignment(Qt.AlignCenter)  # Centrer le titre
        self.title_label.setStyleSheet("""
            QLabel {
                font-size: 36px;
                font-weight: bold;
                color: #4CAF50;
                padding: 20px;
                background-color: #333;
                border-radius: 10px;
            }
        """)

        # Ajouter le logo et le titre dans le header
        header_layout.addWidget(self.logo_label)
        header_layout.addWidget(self.title_label)

        # Ajouter le header à la mise en page principale
        main_layout.addLayout(header_layout)

        # Ajouter les pages au layout
        main_layout.addWidget(self.pages)

        # Ajouter le texte en bas de l'application
        self.footer_label = QLabel("Développé par Med Ammar Bellalah")
        self.footer_label.setAlignment(Qt.AlignCenter)
        self.footer_label.setStyleSheet("""
            QLabel {
                font-size: 12px;
                color: #555;
                padding: 10px;
                background-color: #f0f0f0;
                border-top: 1px solid #ccc;
            }
        """)
        main_layout.addWidget(self.footer_label)

        central_widget = QWidget()
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)

        # Connecter le signal de changement de page
        self.page1.connected.connect(self.show_interaction_page)

        # Configuration du port série
        self.serial_port = QSerialPort()
        self.page1.configure_serial_port(self.serial_port)
        self.page2.configure_serial_port(self.serial_port)

    def show_interaction_page(self):
        self.pages.setCurrentWidget(self.page2)


class SerialConfigPage(QWidget):
    from PySide6.QtCore import Signal
    connected = Signal()

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Configuration Série")

        # Widgets
        self.port_label = QLabel("Port COM :")
        self.port_combo = QComboBox()
        self.baud_label = QLabel("Baud Rate :")
        self.baud_combo = QComboBox()
        self.connect_button = QPushButton("Connecter")

        # Charger les ports disponibles
        self.refresh_ports()

        # Configuration des options de baud rate
        self.baud_combo.addItems(["9600", "115200", "57600", "19200"])

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.port_label)
        layout.addWidget(self.port_combo)
        layout.addWidget(self.baud_label)
        layout.addWidget(self.baud_combo)
        layout.addWidget(self.connect_button)
        self.setLayout(layout)

        # Connexion du bouton
        self.connect_button.clicked.connect(self.connect_serial)

        # Améliorations du style
        self.apply_styles()

    def apply_styles(self):
        # Appliquer un style simple et moderne
        self.setStyleSheet("""
            QWidget {
                font-family: Arial, sans-serif;
                background-color: #f0f0f0;
                border-radius: 10px;
            }
            QLabel {
                font-size: 14px;
                font-weight: bold;
                color: #333;
            }
            QComboBox {
                font-size: 14px;
                padding: 5px;
                background-color: #fff;
                border: 1px solid #ccc;
                border-radius: 5px;
            }
            QPushButton {
                background-color: #4CAF50;
                color: white;
                font-size: 16px;
                padding: 10px;
                border-radius: 5px;
                border: none;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
            QPushButton:pressed {
                background-color: #388e3c;
            }
        """)

    def refresh_ports(self):
        self.port_combo.clear()
        ports = QSerialPortInfo.availablePorts()
        for port in ports:
            self.port_combo.addItem(port.portName())

    def configure_serial_port(self, serial_port):
        self.serial_port = serial_port

    def connect_serial(self):
        port_name = self.port_combo.currentText()
        baud_rate = int(self.baud_combo.currentText())

        self.serial_port.setPortName(port_name)
        self.serial_port.setBaudRate(baud_rate)

        if self.serial_port.open(QSerialPort.ReadWrite):
            print("Connexion réussie au port série.")
            self.connected.emit()
        else:
            print("Échec de la connexion au port série.")


class InteractionPage(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Interaction Série")

        # Widgets
        self.item_label = QLabel("Sélectionner un item :")
        self.item_combo = QComboBox()
        self.item_combo.addItems([f"Item {i+1}" for i in range(9)])
        self.send_button = QPushButton("Envoyer l'item")
        self.received_label = QLabel("Message reçu :")
        self.received_text = QTextEdit()
        self.received_text.setReadOnly(True)

        # Style et visibilité améliorés
        self.received_text.setMinimumHeight(300)
        self.item_combo.setMinimumWidth(200)
        self.send_button.setMinimumHeight(40)

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.item_label)
        layout.addWidget(self.item_combo)
        layout.addWidget(self.send_button)
        layout.addWidget(self.received_label)
        layout.addWidget(self.received_text)
        self.setLayout(layout)

        # Connexion du bouton
        self.send_button.clicked.connect(self.send_item)

        # Améliorations du style
        self.apply_styles()

    def apply_styles(self):
        # Appliquer un style pour l'interface de la page d'interaction
        self.setStyleSheet("""
            QWidget {
                font-family: Arial, sans-serif;
                background-color: #f0f0f0;
                border-radius: 10px;
            }
            QLabel {
                font-size: 14px;
                font-weight: bold;
                color: #333;
            }
            QComboBox {
                font-size: 14px;
                padding: 5px;
                background-color: #fff;
                border: 1px solid #ccc;
                border-radius: 5px;
            }
            QTextEdit {
                font-size: 14px;
                padding: 10px;
                background-color: #fff;
                border: 1px solid #ccc;
                border-radius: 5px;
                }
                QPushButton:hover {
            }
            QPushButton {
                background-color: #4CAF50;
                color: white;
                font-size: 16px;
                padding: 10px;
                border-radius: 5px;
                border: none;
                background-color: #45a049;
            }
            QPushButton:pressed {
                background-color: #388e3c;
            }
        """)

    def configure_serial_port(self, serial_port):
        self.serial_port = serial_port
        self.serial_port.readyRead.connect(self.receive_message)

    def send_item(self):
        selected_item = self.item_combo.currentText()
        if self.serial_port.isOpen():
            self.serial_port.write(selected_item.encode('utf-8'))
            print(f"Envoyé : {selected_item}")

    def receive_message(self):
        if self.serial_port.canReadLine():
            message = self.serial_port.readLine().data().decode('utf-8').strip()
            self.received_text.append(f"Message reçu : {message}")
            print(f"Message reçu : {message}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
