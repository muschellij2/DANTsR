#' @title polylineVoxelCount
#' @description return point coordinates of all voxels with specified label
#' @param mesh 'antsrMesh' of polylines
#' @param reference antsImage that defines the physical space to consider
#' @export

polylineVoxelCount = function(mesh, reference)
{

  if ( !class(mesh)=="antsrMesh") {
    stop("mesh must be an 'antsrMesh'")
  }
  if ( !class(reference)=="antsImage") {
    stop("reference must be an 'antsImage'")
  }

  count = reference*0

  connections = list()
  for ( i in 1:antsrMeshGetNumberOfCells(mesh) ) {
    pts = antsrMeshGetCellPoints(mesh,i)
    idx = round(antsTransformPhysicalPointToIndex(count, pts))
    for ( j in 1:dim(idx)[1] ) {
      skip = FALSE
      if ( j > 1 ) {
        skip = sum(idx[j,]==idx[j-1,])==dim(idx)[2]
      }
      if ( !skip ) {
        if ( indexIsInImage(count, idx[j,]) ) {
          count[ idx[j,1], idx[j,2], idx[j,3] ] = count[ idx[j,1], idx[j,2], idx[j,3] ][1] + 1
        }
        else {
          print(count)
          print(paste("Invalid index: ", idx[j,1], idx[j,2], idx[j,3] ))
        }
      }
    }

  }

  return(count)

}
