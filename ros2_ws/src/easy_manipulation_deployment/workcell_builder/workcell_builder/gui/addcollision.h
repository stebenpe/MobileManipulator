// Copyright 2020 Advanced Remanufacturing and Technology Centre
// Copyright 2020 ROS-Industrial Consortium Asia Pacific Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EASY_MANIPULATION_DEPLOYMENT__WORKCELL_BUILDER__WORKCELL_BUILDER__GUI__ADDCOLLISION_H_
#define EASY_MANIPULATION_DEPLOYMENT__WORKCELL_BUILDER__WORKCELL_BUILDER__GUI__ADDCOLLISION_H_

#include <QDialog>
#include <string>
#include <vector>
#include "attributes/collision.h"
#include "boost/filesystem.hpp"

namespace Ui
{
  class AddCollision; // NOLINT
}

class AddCollision: public QDialog
{
  Q_OBJECT

public:
  bool editing_mode;
  bool success;
  Collision collision;
  std::vector < std::string > available_collisions;
  boost::filesystem::path workcell_path;

  void load_collision(Collision collision);

  int ErrorCheckOrigin();
  int ErrorCollisionName();
  int ErrorCheckGeometry();

  explicit AddCollision(QWidget * parent = nullptr);
  ~AddCollision();

private slots:
  void on_geometry_shape_currentIndexChanged(int index);
  void on_includeorigin_stateChanged(int arg1);
  void on_stl_select_toggled(bool checked);
  void on_collision_name_textChanged(const QString & arg1);
  void on_exit_clicked();
  void on_MeshFIle_clicked();
  void keyPressEvent(QKeyEvent * e);
  void on_ok_clicked();

private:
  Ui::AddCollision * ui;
};

#endif  // EASY_MANIPULATION_DEPLOYMENT__WORKCELL_BUILDER__WORKCELL_BUILDER__GUI__ADDCOLLISION_H_
