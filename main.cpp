#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/doublearea.h>
#include <stan/math.hpp>
#include <iostream>

template <typename DerivedV>
typename DerivedV::Scalar total_surface_area(
    const Eigen::MatrixBase<DerivedV> & V,
    const Eigen::MatrixXi & F)
{
  Eigen::Matrix<typename DerivedV::Scalar,Eigen::Dynamic,1> A;
  igl::doublearea(V, F, A);
  return 0.5*A.sum();
}

int main(int argc, char *argv[])
{
   // read ../decimated-knight.off or argv[1]
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::read_triangle_mesh(
      argc>1?argv[1]:"../decimated-knight.obj", V, F);

  // C++20 templated lambda version of total_surface_area taking V_vec
  auto total_surface_area = [&F]<typename T>
    (const Eigen::Matrix<T, Eigen::Dynamic, 1> & V_vec) -> T
  {
    Eigen::Map<const Eigen::Matrix<T, Eigen::Dynamic, 3> > V(V_vec.data(),V_vec.size()/3,3);
    Eigen::Matrix<T, Eigen::Dynamic, 1> A;
    igl::doublearea(V, F, A);
    return 0.5*A.sum();
  };

  Eigen::VectorXd U_vec = V.reshaped();
  Eigen::VectorXd dfdU_vec;
  double a;
  stan::math::gradient( total_surface_area, U_vec, a, dfdU_vec);
  Eigen::Map<Eigen::MatrixXd> dfdU(dfdU_vec.data(),V.rows(),V.cols());

  // Draw the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  // Draw dfdU as little white lines from each vertex
  const double scale = 
    0.1 * 
    (V.colwise().maxCoeff()-V.colwise().minCoeff()).norm()/
    dfdU.rowwise().norm().maxCoeff();
  viewer.data().add_edges(V,(V + dfdU*scale).eval(), Eigen::RowVector3d(1,1,1) );
  viewer.data().line_width = 1;
  viewer.launch();
}
