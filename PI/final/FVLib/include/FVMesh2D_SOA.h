#pragma once

#include <string>
#include <vector>
#include <FV>
using namespace std;

namespace FVL {


	class FVMesh2D_SOA {

		public:
			unsigned int num_edges;
			vector<FVEdge2D> edges;

			unsigned int num_vertex;
			FVPoint2D<double> vertex_coords;

			unsigned int num_cells;
			FVPoint2D<double> centroids;
			

		private:					


	}

}
