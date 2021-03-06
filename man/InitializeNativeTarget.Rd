\name{InitializeNativeTarget}
\alias{InitializeNativeTarget}
\title{Initialize the LLVM engine for JIT operations}
\description{
  If one is to use any of LLVM's JIT operations in
  the R session, one needs to call this function
  in order to ensure that the relevant initialization
  is done for the particular host.
}
\usage{
InitializeNativeTarget()
}
%- maybe also 'usage' for other objects documented here.
\value{
 A logical value.
}
\references{
 \url{http://llvm.org/docs/doxygen/html/namespacellvm.html}
}
\author{
Duncan Temple Lang
}

\seealso{

}
\examples{

}
\keyword{programming}

