// --------------------------------------------------------------------
// This file is part of libDistMesh.
//
// libDistMesh is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libDistMesh is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libDistMesh. If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2015 Patrik Gebhardt
// Contact: patrik.gebhardt@rub.de
// --------------------------------------------------------------------

#include <stdio.h>

#include <delaunator.hpp>

#include "distmesh/distmesh.h"
#include "distmesh/triangulation.h"

Eigen::ArrayXXi distmesh::triangulation::delaunay(
    Eigen::Ref<Eigen::ArrayXXd const> const points) {

    std::vector<double> coords;
    for (int n = 0; n < points.rows(); ++n) {
        coords.push_back(points(n, 0));
        coords.push_back(points(n, 1));
    }

    delaunator::Delaunator d(coords);

    int nMax = d.triangles.size()/3;
    Eigen::ArrayXXi triangulation(nMax, 3);
    for (int n = 0; n < nMax; ++n) {
        triangulation(n, 0) = d.triangles[3*n];
        triangulation(n, 1) = d.triangles[3*n + 1];
        triangulation(n, 2) = d.triangles[3*n + 2];
    }
    return triangulation;
}
