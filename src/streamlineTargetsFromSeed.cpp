#include <string>
#include "streamlineTargetsFromSeed.h"
#include "itkStreamlineTargetsFromSeedCellFunction.h"

template< class MeshType, class ImageType >
SEXP streamlineTargetsFromSeed( SEXP r_mesh, SEXP r_image, SEXP r_seeds, SEXP r_index )
{
  using MeshPointerType = typename MeshType::Pointer;
  using FunctionType = itk::StreamlineTargetsFromSeedCellFunction<MeshType, ImageType>;
  using FunctionPointerType = typename FunctionType::Pointer;

  using ImagePointerType = typename ImageType::Pointer;

  MeshPointerType mesh = Rcpp::as<MeshPointerType>(r_mesh);
  if ( ! mesh.IsNotNull() )
    {
    Rcpp::stop("mesh not yet allocated");
    }
  ImagePointerType image = Rcpp::as<ImagePointerType>(r_image);
  if ( ! image.IsNotNull() )
    {
    Rcpp::stop("mask not yet allocated");
    }


  Rcpp::NumericVector indices( r_index );
  Rcpp::NumericMatrix hits( indices.size(), 2 );

  FunctionPointerType function = FunctionType::New();
  function->SetInputMesh( mesh );
  function->SetImage( image );

  for (unsigned long i=0; i<indices.size(); i++ ) {
    itk::FixedArray<unsigned long,2> iHit = function->Evaluate( indices[i]-1 );
    hits(i,0) = iHit[0];
    hits(i,1) = iHit[1];
  }

  return( Rcpp::wrap(hits) );

}

RcppExport SEXP streamlineTargetsFromSeed( SEXP r_mesh, SEXP r_image, SEXP r_seeds, SEXP r_index )
{
try
{
  if( r_mesh == nullptr )
    {
    Rcpp::Rcout << "Unspecified Argument (mesh)" << std::endl ;
    return Rcpp::wrap( 1 ) ;
    }

  if( r_image == nullptr )
    {
    Rcpp::Rcout << "Unspecified Argument (image)" << std::endl ;
    return Rcpp::wrap( 1 ) ;
    }

  Rcpp::S4 mesh( r_mesh );
  Rcpp::S4 image( r_image );
  unsigned int dimension = Rcpp::as< unsigned int >( mesh.slot( "dimension" ) );
  std::string precision = Rcpp::as< std::string >( mesh.slot( "precision" ) );

  unsigned int imageDimension = Rcpp::as< unsigned int >( image.slot( "dimension" ) );
  std::string iPrecision = Rcpp::as< std::string >( image.slot( "precision" ) );

  if ( ( dimension < 2) || ( dimension > 3)  )
  {
    Rcpp::stop("Invalid mesh dimension");
  }

  if ( dimension != imageDimension ) {
    Rcpp::stop("Mesh and image must have the same dimension");
  }

  if ( precision != iPrecision ) {
    Rcpp::stop("Mesh and image must have the same precision");
  }

  if ( precision=="double") {
    using PrecisionType = double;
    if (dimension == 2)
      {
      using MeshType = itk::Mesh<PrecisionType,2>;
      using ImageType = itk::Image<PrecisionType,2>;
      return streamlineTargetsFromSeed<MeshType, ImageType>( r_mesh, r_image, r_seeds, r_index );
      }
    else if (dimension == 3)
      {
      using MeshType = itk::Mesh<PrecisionType,3>;
      using ImageType = itk::Image<PrecisionType,3>;
      return streamlineTargetsFromSeed<MeshType, ImageType>( r_mesh, r_image, r_seeds, r_index );
      }
    }
  else if ( precision=="float") {
    using PrecisionType = float;
    if (dimension == 2)
      {
      using MeshType = itk::Mesh<PrecisionType,2>;
      using ImageType = itk::Image<PrecisionType,2>;
      return streamlineTargetsFromSeed<MeshType, ImageType>( r_mesh, r_image, r_seeds, r_index );
      }
    else if (dimension == 3)
      {
      using MeshType = itk::Mesh<PrecisionType,3>;
      using ImageType = itk::Image<PrecisionType,3>;
      return streamlineTargetsFromSeed<MeshType, ImageType>( r_mesh, r_image, r_seeds, r_index );
      }
    }
  else
  {
    Rcpp::stop("Invalid precision");
  }

  // Never reached
  return(Rcpp::wrap(NA_REAL));

  }
catch( itk::ExceptionObject & err )
  {
  Rcpp::Rcout << "ITK ExceptionObject caught !" << std::endl;
  Rcpp::Rcout << err << std::endl;
  Rcpp::stop("ITK exception caught");
  }
catch( const std::exception& exc )
  {
  forward_exception_to_r( exc ) ;
  }
catch(...)
  {
	Rcpp::stop("c++ exception (unknown reason)");
  }
return Rcpp::wrap(NA_REAL); //not reached
}
