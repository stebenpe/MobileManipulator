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


#ifndef YAML_PARSER__VISUAL_PARSER_H_
#define YAML_PARSER__VISUAL_PARSER_H_

#include <string>

#include "yaml-cpp/yaml.h"

#include "attributes/visual.h"
#include "yaml_parser/geometry_parser.h"
#include "yaml_parser/origin_parser.h"
#include "yaml_parser/material_parser.h"


struct VisualParser
{
  std::string name;
  Geometry geometry;
  Origin origin;
  Material material;

  bool is_origin;
  bool is_material;


  static void generate_visual(YAML::Emitter *** out, Visual visual)
  {
    // ***out<<YAML::BeginMap;
    *** out << YAML::Key << "visual";
    *** out << YAML::Value;
    *** out << YAML::BeginMap;

    *** out << YAML::Key << "name";
    *** out << YAML::Value << visual.name;
    GeometryParser::generate_geometry(&out, visual.geometry);

    if (visual.is_origin) {
      OriginParser::generate_origin(&out, visual.origin);
    }

    if (visual.is_material) {
      MaterialParser::generate_material(&out, visual.material);
    }
    *** out << YAML::EndMap;
    // ***out<<YAML::EndMap;
  }
};

#endif  // YAML_PARSER__VISUAL_PARSER_H_
