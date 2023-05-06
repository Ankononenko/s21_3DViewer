/*! \mainpage 3D Viewer
 *
 * \section Documentation Documentation describes the components of the 3D
 * Viewer applicaton
 *
 * Shortcuts: \n
 * \b Q \b - Quit; \n
 * \b R \b - Record screencast \n
 * \b NUM 4 \b - Move model to the left \n
 * \b NUM 6 \b - Move model to the right \n
 * \b NUM 8 \b - Move model up \n
 * \b NUM 2 \b - Move model down \n
 * \b - \b - Scale model down \n
 * \b + \b - Scale model up \n
 * \b Ctrl + NUM 4 \b - Rotate model to the left \n
 * \b Ctrl + NUM 6 \b - Rotate model to the right \n
 * \b Ctrl + NUM 8 \b - Rotate model up \n
 * \b Ctrl + NUM 2 \b - Rotate model down \n
 * \b Ctrl + NUM 1 \b - Rotate model clockwise \n
 * \b Ctrl + NUM 9 \b - Rotate model couterclowise \n
 */

#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"
/*!
 * \brief MainWindow::MainWindow
 *
 * Constructor for the MainWindow class. Sets up the user interface and
 * initializes the necessary connections and widgets.
 *
 * \param parent The parent widget for this MainWindow.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  glWidget = this->findChild<GLWidget *>("openGLWidget");
  if (glWidget) {
    glWidget->filenameLabel = ui->filenameLabel;
  }
  connect(glWidget, &GLWidget::modelLoaded, this, &MainWindow::onModelLoaded);
  numVerticesLabel = ui->numVerticesLabel;
  numEdgesLabel = ui->numEdgesLabel;
  screencastTimer = new QTimer(this);
  screencastFrameCount = 0;
  connect(screencastTimer, &QTimer::timeout, this,
          &MainWindow::captureScreencastFrame);
}
/*!
 * \brief MainWindow::~MainWindow
 *
 * Destructor for the MainWindow class. Cleans up the user interface.
 */
MainWindow::~MainWindow() { delete ui; }
/*!
 * \brief MainWindow::on_QuitButton_clicked
 * Function closes the applicaton
 */
void MainWindow::on_QuitButton_clicked() { close(); }
/*!
 * \brief MainWindow::on_loadModelFileButton_clicked
 * Function is used to load the file using the QFileDialog to open the file
 * dialog. All .obj files are displayed. Absolute path is loaded.
 */
void MainWindow::on_loadModelFileButton_clicked() {
  QString fileFilter = "OBJ Files (*.obj);;All Files (*)";
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Load Model File"), "", fileFilter);

  if (!fileName.isEmpty()) {
    qDebug() << "Selected file:" << fileName;
    QFileInfo fileInfo(fileName);
    QString absoluteFilePath = fileInfo.absoluteFilePath();
    qDebug() << "Absolute file path:" << absoluteFilePath;
    glWidget->loadModel(absoluteFilePath);
  }
}
/*!
 * \brief MainWindow::on_changeBGColorButton_clicked
 * Function is used to change the default BG color. QColorDialog is used to
 * update. Updates the initialColor
 */
void MainWindow::on_changeBGColorButton_clicked() {
  QColor initialColor = glWidget->getBackgroundColor();
  QColor newColor =
      QColorDialog::getColor(initialColor, this, tr("Select Background Color"));

  if (newColor.isValid()) {
    glWidget->setBackgroundColor(newColor);
    glWidget->update();
  }
}
/*!
 * \brief MainWindow::on_moveUpButton_clicked
 * Moves up the model. Uses moveModel function of glWidget
 */
void MainWindow::on_moveUpButton_clicked() { glWidget->moveModel(0, 0.1f, 0); }

void MainWindow::on_moveDownButton_clicked() {
  glWidget->moveModel(0, -0.1f, 0);
}

void MainWindow::on_moveLeftButton_clicked() {
  glWidget->moveModel(-0.1f, 0, 0);
}

void MainWindow::on_moveRightButton_clicked() {
  glWidget->moveModel(0.1f, 0, 0);
}

void MainWindow::on_moveForwardButton_clicked() {
  glWidget->moveModel(0, 0, 0.1f);
}

void MainWindow::on_moveBackwardButton_clicked() {
  glWidget->moveModel(0, 0, -0.1f);
}

void MainWindow::on_smallerButton_clicked() { glWidget->scaleModel(0.9f); }

void MainWindow::on_biggerButton_clicked() { glWidget->scaleModel(1.1f); }

void MainWindow::on_rotateUpButton_clicked() {
  glWidget->rotateModel(-10.0f, 0.0f, 0.0f);
}

void MainWindow::on_rotateDownButton_clicked() {
  glWidget->rotateModel(10.0f, 0.0f, 0.0f);
}

void MainWindow::on_rotateLeftButton_clicked() {
  glWidget->rotateModel(0.0f, -10.0f, 0.0f);
}

void MainWindow::on_rotateRightButton_clicked() {
  glWidget->rotateModel(0.0f, 10.0f, 0.0f);
}

void MainWindow::on_rotateClockwiseButton_clicked() {
  glWidget->rotateModel(0.0f, 0.0f, -10.0f);
}

void MainWindow::on_rotateCounterclockwiseButton_clicked() {
  glWidget->rotateModel(0.0f, 0.0f, 10.0f);
}

void MainWindow::on_parallelButton_clicked() {
  glWidget->setParallelProjection();
}

void MainWindow::on_centralButton_clicked() {
  glWidget->setCentralProjection();
}

void MainWindow::on_solidButton_clicked() {
  // 0x00FF is a hexadecimal representation of a 16-bit binary number.
  // In this case, it represents the pattern 0000 0000 1111 1111 in binary,
  // which is used for line stippling. When you use 0x00FF as the pattern,
  // it alternates between one visible pixel and one hidden pixel, creating a
  // dashed line effect.
  glWidget->setEdgeLineStyle(0xFFFF, 1);
}

void MainWindow::on_dashedButton_clicked() {
  glWidget->setEdgeLineStyle(0x00FF, 1);
}

void MainWindow::on_thinnerButton_clicked() { glWidget->setEdgeWidth(-0.5f); }

void MainWindow::on_thickerButton_clicked() { glWidget->setEdgeWidth(0.5f); }

void MainWindow::on_edgesColorButton_clicked() {
  QColor initialColor = Qt::white;
  QColor newColor =
      QColorDialog::getColor(initialColor, this, tr("Select Edge Color"));

  if (newColor.isValid()) {
    glWidget->setEdgeColor(newColor);
  }
}

void MainWindow::on_verticesDecreaseSizeButton_clicked() {
  glWidget->changeVertexSize(-1.0f);
}

void MainWindow::on_verticesIncreaseSizeButton_clicked() {
  glWidget->changeVertexSize(1.0f);
}

void MainWindow::on_verticesColorButton_clicked() {
  QColor initialColor = Qt::white;
  QColor newColor =
      QColorDialog::getColor(initialColor, this, tr("Select Vertex Color"));

  if (newColor.isValid()) {
    glWidget->setVertexColor(newColor);
  }
}

void MainWindow::on_noneDisplayMethodButton_clicked() {
  glWidget->setVertexDisplayMethod(GLWidget::None);
}

void MainWindow::on_squareDisplayMethodButton_clicked() {
  glWidget->setVertexDisplayMethod(GLWidget::Square);
}

void MainWindow::on_circleDisplayMethodButton_clicked() {
  glWidget->setVertexDisplayMethod(GLWidget::Circle);
}

void MainWindow::onModelLoaded(int numVertices, int numEdges) {
  numVerticesLabel->setText(QString("Vertices: %1").arg(numVertices));
  numEdgesLabel->setText(QString("Edges: %1").arg(numEdges));
}

void MainWindow::on_screenshotButton_clicked() {
  QImage screenshot = glWidget->takeScreenshot();
  QString fileFilter =
      "PNG Files (*.png);;JPEG Files (*.jpg *.jpeg);;BMP Files (*.bmp);;All "
      "Files (*)";
  QString fileName =
      QFileDialog::getSaveFileName(this, tr("Save Screenshot"), "", fileFilter);

  if (!fileName.isEmpty()) {
    QFileInfo fileInfo(fileName);
    QString fileExtension = fileInfo.suffix().toLower();

    if (fileExtension.isEmpty() ||
        !(fileExtension == "png" || fileExtension == "jpg" ||
          fileExtension == "jpeg" || fileExtension == "bmp")) {
      fileName += ".png";
    }

    screenshot.save(fileName);
  }
}
/*!
 * \brief MainWindow::on_screencastButton_clicked
 *
 * Starts or stops the screencast recording. When the recording is stopped, it
 * saves the frames as PNG images, creates a GIF from the images, and deletes
 * the saved PNG images.
 */
// sudo apt install imagemagick
void MainWindow::on_screencastButton_clicked() {
  if (!screencastTimer->isActive()) {
    // Start recording
    screencastFrameCount = 0;
    screencastFrames.clear();
    screencastTimer->start(100);  // Capture every 100 ms
    ui->screencastButton->setText("Stop Recording");
  } else {
    // Stop recording
    screencastTimer->stop();
    // Save the frames as PNG images
    QStringList imageFilenames;
    for (int i = 0; i < screencastFrames.count(); ++i) {
      const QImage &frame = screencastFrames.at(i);
      QString fileName =
          QString("screencast_frame_%1.png").arg(i, 3, 10, QChar('0'));
      if (!frame.save(fileName)) {
        qDebug() << "Error saving frame:" << fileName;
        break;
      }
      imageFilenames << fileName;
    }

    // Open the file picker for saving the GIF
    QString fileFilter = "GIF Files (*.gif);;All Files (*)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Screencast"),
                                                    "", fileFilter);

    if (!fileName.isEmpty()) {
      QFileInfo fileInfo(fileName);
      QString fileExtension = fileInfo.suffix().toLower();

      if (fileExtension.isEmpty() || fileExtension != "gif") {
        fileName += ".gif";
      }

      // Create a GIF from the saved PNG images
      createGifFromImages(fileName, imageFilenames, 10);
    }
    screencastFrames.clear();
    ui->screencastButton->setText("Start Recording");
    // Delete the saved PNG images
    for (const QString &filename : imageFilenames) {
      QFile::remove(filename);
    }
  }
}
/*!
 * \brief MainWindow::captureScreencastFrame
 *
 * Captures a frame from the GLWidget, resizes it, and appends it to the
 * screencastFrames list. Stops the recording if the screencast frame count
 * reaches 50 (5 seconds at 10 fps).
 */
void MainWindow::captureScreencastFrame() {
  QImage frame = glWidget->grabFramebuffer();
  QImage scaledFrame = frame.scaled(640, 480, Qt::KeepAspectRatio);

  screencastFrames.append(scaledFrame);
  screencastFrameCount++;
  // 5 seconds at 10 fps
  if (screencastFrameCount >= 50) {
    // Stop recording
    on_screencastButton_clicked();
  }
}
/*!
 * \brief MainWindow::createGifFromImages
 *
 * Creates a GIF from the provided list of image filenames using the 'convert'
 * command. The delay parameter determines the time between frames in the GIF.
 *
 * \param gifFilename The filename of the output GIF file.
 * \param imageFilenames A list of filenames of the images to be included in the
 * GIF. \param delay The delay between frames in the GIF, in milliseconds.
 */
void MainWindow::createGifFromImages(const QString &gifFilename,
                                     const QStringList &imageFilenames,
                                     int delay) {
  if (imageFilenames.isEmpty()) {
    qDebug() << "No images provided";
    return;
  }

  QProcess process;
  QStringList arguments;

  arguments << "-delay" << QString::number(delay);
  arguments << imageFilenames;
  arguments << gifFilename;

  process.start("convert", arguments);
  process.waitForFinished(-1);

  if (process.exitStatus() == QProcess::NormalExit) {
    qDebug() << "GIF created:" << gifFilename;
  } else {
    qDebug() << "Failed to create GIF:" << process.errorString();
  }
}

void MainWindow::on_resetPreferencesButton_clicked() {
  glWidget->resetPreferences();
}

void MainWindow::on_yMoveDoubleSpinBox_editingFinished() {
  double value = ui->yMoveDoubleSpinBox->value();
  glWidget->moveModel(0, value, 0);
}

void MainWindow::on_xMoveDoubleSpinBox_editingFinished() {
  double value = ui->xMoveDoubleSpinBox->value();
  glWidget->moveModel(value, 0, 0);
}

void MainWindow::on_zMoveDoubleSpinBox_editingFinished() {
  double value = ui->zMoveDoubleSpinBox->value();
  glWidget->moveModel(0, 0, value);
}

void MainWindow::on_sizeDoubleSpinBox_editingFinished() {
  double value = ui->sizeDoubleSpinBox->value();
  glWidget->scaleModel(value);
}

void MainWindow::on_xRotateDoubleSpinBox_editingFinished() {
  double value = ui->xRotateDoubleSpinBox->value();
  glWidget->rotateModel(value, 0.0f, 0.0f);
}

void MainWindow::on_yRotateDoubleSpinBox_editingFinished() {
  double value = ui->yRotateDoubleSpinBox->value();
  glWidget->rotateModel(0.0f, value, 0.0f);
}

void MainWindow::on_zRotateDoubleSpinBox_editingFinished() {
  double value = ui->zRotateDoubleSpinBox->value();
  glWidget->rotateModel(0.0f, 0.0f, value);
}
