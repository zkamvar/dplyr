#include <dplyr.h>

using namespace Rcpp ;
using namespace dplyr ;

// [[Rcpp::export]]
SEXP distinct_impl( DataFrame df, CharacterVector vars, CharacterVector keep){
    if( df.size() == 0 )
        return df ;
    check_valid_colnames(df) ;
    if( !vars.size() ){
        vars = df.names() ;
    }
    DataFrameVisitors visitors(df, vars) ;

    std::vector<int> indices ;
    VisitorSetIndexSet<DataFrameVisitors> set(visitors) ;

    int n = df.nrows() ;
    for( int i=0; i<n; i++){
        if( set.insert(i).second ){
            indices.push_back(i) ;
        }
    }

    return DataFrameSubsetVisitors(df, keep).subset(indices, df.attr("class")) ;
}
