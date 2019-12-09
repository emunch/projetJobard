#include "my_scene.h"

#include <iostream>
#include <math.h>
#include <GL/gl.h>  // OpenGL include file
#include <GL/glut.h>
#include <QGLWidget>

using namespace std;

/** 
 * Constructor
 * 
 * @param radius 
 */
MyScene::MyScene(float radius)
{
  std::cout << "constructing :  MyScene" << std::endl;

  _NB_TEX = 2;
  texNames = new GLuint[_NB_TEX];

  _currentObject = MyScene::TEXTURED_SHAPES;
  _numberOfObjects = 2;	         // increment it when you add a new 3D object!
 
  _displayMode = MyScene::FLATSHADED;

  _radius = radius;

  _radiusMin = 0.1;
  _radiusMax = 2.0;
  _radiusIncr = 0.1;
}

/** 
 * Destructor
 * 
 */
MyScene::~MyScene()
{
  std::cout<<"~MyScene"<<std::endl;
  
  delete [] texNames;
}

/** 
 * Init the scene and OpenGL state
 * 
 */
void MyScene::init()
{
  glColor3f(0.5, 0., 0.);

  // set antialiased lines
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glLineWidth(1.5);

  glEnable(GL_NORMALIZE); // normalize normal vectors when objects are
			  // scaled

  // Read images from file
  QImage* imgGray = this->loadImage("./brick_grise.jpg");
  QImage* imgRed  = this->loadImage("./brick_rouge.jpg");
  
  // Generate two texture objects
  glGenTextures(_NB_TEX, texNames);

  // Define the first texture and bind it to texNames[0]
  if (imgRed != NULL) {
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imgRed->width(),imgRed->height()
		 ,0, GL_RGBA,GL_UNSIGNED_BYTE, imgRed->bits());
  }
  // Define the second texture and bind it to texNames[1]
  if (imgGray != NULL) {
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, imgGray->width(),imgGray->height()
		 ,0, GL_RGBA,GL_UNSIGNED_BYTE, imgGray->bits());
  }
  
  delete imgRed;
  delete imgGray;
}

/** 
 * Load an image from disk and convert it to a suitable format for OpenGL
 * 
 * @param filename 
 * 
 * @return a pointer on an image than can be used as a texture
 */
QImage* MyScene::loadImage(std::string filename)
{
  // load image
  QImage img(filename.c_str());

  if (img.isNull()) {
    cerr << "Unable to load " << filename << endl;
    return NULL;
  }

  cout << "Loading " << filename << ", " 
       << img.width() << "x" << img.height() << " pixels" << endl;

  
  // For a more secure and general texture loading procedure, have a
  // look at:
  // http://artis.imag.fr/~Gilles.Debunne/QGLViewer/examples/textureViewer.html

  // convert it to suitable OpenGL 
  QImage* glImg = new QImage(QGLWidget::convertToGLFormat(img));

  return glImg;
}

/** 
 * Draw the scene
 * 
 */
void MyScene::draw()
{
  glPushMatrix();
  glScalef(_radius/2, _radius/2, _radius/2);

  switch(_currentObject%_numberOfObjects) {
  case MyScene::CUBE: // Draw the cube
    _cube.draw();
    break;
  case MyScene::TEXTURED_SHAPES: // Draw the axis

    //_texturedShapes.draw();

    glPushMatrix();
    glScalef(0.5,0.5,1.0);
    glTranslatef(-2.5,2,0);
  
    // appel de la premiere texture
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glNormal3f(0,0,1);

    glTexCoord2f(0,0);  glVertex3f(0,0,0);
    glTexCoord2f(1,0);  glVertex3f(1,0,0);
    glTexCoord2f(1,1);  glVertex3f(1,1,0);
    glTexCoord2f(0,1);  glVertex3f(0,1,0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glTranslatef(1.5,0,0);

    glBegin(GL_QUADS);
    glNormal3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1.5,1,0);
    glVertex3f(0.5,1,0);
    glEnd();

    glTranslatef(1.5,0,0);
  
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(0.5,1,0);
    glEnd();

    glTranslatef(1.5,0,0);

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(0.5,1,0);
    glEnd();

    glTranslatef(-4.5,-.5,0);
  
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,-1,0);
    glVertex3f(0,-1,0);

    glVertex3f(0,-1,0);
    glVertex3f(1,-1,0);
    glVertex3f(1,-2,0);
    glVertex3f(0,-2,0);

    glVertex3f(0,-2,0);
    glVertex3f(1,-2,0);
    glVertex3f(1,-3,0);
    glVertex3f(0,-3,0);
    glEnd();

    glTranslatef(1.5,0,0);

    glBegin(GL_QUADS);
    glNormal3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,-3,0);
    glVertex3f(0,-3,0);
    glEnd();
  
    glTranslatef(2.75,-1.5,0);
    glPushMatrix();
    glScalef(5./4., 5./4., 5./4.);

    // le disque a completer
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glEnd();

    glPopMatrix();

    glTranslatef(-4.25, -3, 0);
    glScalef(5.5,1,1);

    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0,0,1);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(0,1);
    glVertex2f(1,1);
    glEnd();

    glPopMatrix();

    break;
    
    //... insert here the other objects

  }

  glPopMatrix();

}

/** 
 * Slot set current object
 * 
 * @param currentObject
 */
void MyScene::slotSetCurrentObject(int currentObject)
{
  std::cout << "slotSetCurrentObject "<< currentObject << std::endl;
  _currentObject = currentObject;
  emit sigCurrentObjectChanged(currentObject);
  
}

/** 
 * Slot set display mode
 * 
 * @param currentObject
 */
void MyScene::slotSetDisplayMode(int displayMode)
{
  std::cout << "slotSetDisplayMode "<< displayMode%3 << std::endl;
  _displayMode = displayMode;

  switch (displayMode%3) {
  case MyScene::WIREFRAME:
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    
    break;
  case MyScene::FLATSHADED: 
    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
  case MyScene::SMOOTHSHADED:
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
  }

  emit sigDisplayModeChanged(displayMode);
}

/** 
 * Slot set radius
 * 
 * @param radius 
 */
void MyScene::slotSetRadius(double radius)
{
  if (fabs(_radius - float(radius))>1e-6) {
    //std::cout << "slotSetRadius "<< radius << std::endl;
    _radius = radius;
    emit sigRadiusChanged(radius);
  }
}

/** 
 * Process keyboard events for QGLViewer widget
 * 
 * @param e a keyboard event from QGLViewer 
 * 
 * @return true if the event has been handled
 */
bool MyScene::keyPressEvent(QKeyEvent *e)
{
  const Qt::KeyboardModifiers modifiers = e->modifiers();

  // A simple switch on e->key() is not sufficient if we want to take
  // state key into account.  With a switch, it would have been
  // impossible to separate 'F' from 'CTRL+F'.  That's why we use
  // imbricated if...else and a "handled" boolean.

  bool handled = false;

  float epsilon = 1e-5;  // for float comparison
  
  // Increase radius with 'r'
  if ((e->key()==Qt::Key_R) && (modifiers==Qt::NoButton)) {
    if (_radius+_radiusIncr <= _radiusMax + epsilon)
      this->slotSetRadius(_radius+_radiusIncr);
    handled = true;
  } 
  // Decrease radius with 'R'
  else if ((e->key()==Qt::Key_R) && (modifiers==Qt::SHIFT)) {
    if (_radius-_radiusIncr >= _radiusMin - epsilon)
      this->slotSetRadius(_radius-_radiusIncr);
    handled = true;
  }
      
  // Increase current displayed object with 'o'
  if ((e->key()==Qt::Key_O) && (modifiers==Qt::NoButton)) { 
    this->slotSetCurrentObject(_currentObject+1);
    handled = true;
  } 
  // Decrease current displayed object with 'O'
  else if ((e->key()==Qt::Key_O) && (modifiers==Qt::SHIFT)) {
    this->slotSetCurrentObject(_currentObject-1);
    handled = true;
  }
      
  // change displau mode with 's'
  else if ((e->key()==Qt::Key_S) && (modifiers==Qt::NoButton)) {
    this->slotSetDisplayMode(_displayMode+1);
    handled = true;
  }
  
  
  
      // ... and so on with other else/if blocks.

  return handled;
}
