
<!-- README.md is generated from README.Rmd. Please edit that file -->

# DANTsR

![dantsr
killers](http://www.picslyrics.net/images/255741-the-killers-are-we-human-or-are-we-dancer.jpg)

<!-- badges: start -->

[![Travis build
status](https://travis-ci.org/jeffduda/DANTsR.svg?branch=master)](https://travis-ci.org/jeffduda/DANTsR)
[![muschellij2 Travis build
status](https://travis-ci.com/muschellij2/DANTsR.svg?branch=master)](https://travis-ci.com/muschellij2/DANTsR)

<!-- badges: end -->

The goal of DANTsR is to provide diffusion imaging extension to ANTsR.

## Installation

You can install the released version of DANTsR from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("DANTsR")
```

And the development version from [GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("jeffduda/DANTsR")
```

## Example

``` r
library(DANTsR)
img = antsImageRead("yourfile.nii.gz")
fa = dtiAnisotrpyImage(img, "FractionalAnisotropy")
ra = dtiAnisotropyImage(img, "RelativeAnisotropy")
eig = dtiEigenSystem(img)
dec = dtiColorMap(img)
seeds = labelsToPoints( fa > 0.1 )
```
