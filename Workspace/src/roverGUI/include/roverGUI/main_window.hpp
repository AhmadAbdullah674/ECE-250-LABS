/**
 * @file /include/roverGUI/main_window.hpp
 *
 * @brief Qt based gui for roverGUI.
 *
 * @date November 2010
 **/
#ifndef roverGUI_MAIN_WINDOW_H
#define roverGUI_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/


#include "ui_main_window.h"
#include <QtCore>
#include <QtGui/QMainWindow>
#include <QApplication>
#include <QtGui>


#include <sensor_msgs/NavSatFix.h>
#include <robot_localization/navsat_conversions.h>

#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace roverGUI {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  Ui::MainWindowDesign ui;
  MainWindow(int argc, char **argv, QWidget *parent = 0);
  ~MainWindow();

  void subscriber_callback(const sensor_msgs::NavSatFix::ConstPtr &receivedMsg);
  float scaling_function(float x_dist, float y_dist);

private:
  QGraphicsScene *scene;
  double longitude;
  double latitude;
  double easting_utm;
  double northing_utm;
  std::string utm_zone, rover_utm_zone;

public Q_SLOTS:
  void on_longitudeLineEdit_returnPressed();
  void on_latitudeLineEdit_returnPressed();
};

} // namespace roverGUI

#endif // roverGUI_MAIN_WINDOW_H
