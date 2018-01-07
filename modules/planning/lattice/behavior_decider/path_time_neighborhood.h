/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef MODULES_PLANNING_LATTICE_BEHAVIOR_DECIDER_PATH_TIME_NEIGHBORHOOD_H_
#define MODULES_PLANNING_LATTICE_BEHAVIOR_DECIDER_PATH_TIME_NEIGHBORHOOD_H_

#include <array>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "modules/common/proto/geometry.pb.h"
#include "modules/planning/proto/lattice_structure.pb.h"
#include "modules/planning/common/frame.h"
#include "modules/planning/reference_line/reference_line.h"
#include "modules/planning/common/obstacle.h"

namespace apollo {
namespace planning {

class PathTimeNeighborhood {
 public:
  PathTimeNeighborhood(
      const Frame* frame, const double ego_s,
      const ReferenceLine& reference_line,
      const std::vector<common::PathPoint>& discretized_ref_points);

  std::vector<PathTimeObstacle> GetPathTimeObstacles() const;

  bool GetPathTimeObstacle(const std::string& obstacle_id,
                           PathTimeObstacle* path_time_obstacle);

  double SpeedAtT(
      const std::string& obstacle_id, const double s, const double t) const;

 private:
  void SetupObstacles(
      const Frame* frame, const ReferenceLine& reference_line,
      const std::vector<common::PathPoint>& discretized_ref_points);

  PathTimePoint SetPathTimePoint(const std::string& obstacle_id,
                                 const double s,
                                 const double t) const;

  void SetStaticPathTimeObstacle(const Obstacle* obstacle,
                                 const ReferenceLine& reference_line);

 private:
  double ego_s_;

  // obstacle_id -> critical conditions
  std::unordered_map<std::string, PathTimeObstacle> path_time_obstacle_map_;

  std::unordered_map<std::string, prediction::Trajectory> prediction_traj_map_;

  std::vector<apollo::common::PathPoint> discretized_ref_points_;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_LATTICE_BEHAVIOR_DECIDER_PATH_TIME_NEIGHBORHOOD_H_