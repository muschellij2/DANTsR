% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/antsrRegistration_class.R
\name{antsrRegistrationRun}
\alias{antsrRegistrationRun}
\title{antsrRegistrationRun}
\usage{
antsrRegistrationRun(stages, fixed, moving)
}
\arguments{
\item{stages}{antsrRegistration parameters}

\item{fixed}{fixed image}

\item{moving}{moving image}
}
\value{
antsrMesh
}
\description{
run a linear registration
}
\examples{
x =  antsrMeshCreate( 3, "float", reserve=128 )
}
