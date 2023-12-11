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


#ifndef ATTRIBUTES__VISUAL_H_
#define ATTRIBUTES__VISUAL_H_

#include <string>

#include "attributes/geometry.h"
#include "attributes/material.h"
#include "attributes/origin.h"


struct Visual
{
  std::string name;
  Geometry geometry;
  Origin origin;
  Material material;

  bool is_origin = false;
  bool is_material = false;
};

#endif  // ATTRIBUTES__VISUAL_H_
