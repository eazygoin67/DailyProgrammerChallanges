import math

##### VALIDATION #####

def validateSquare( magicSquare ):

    # Get Dimensions of the Square
    size = int(math.sqrt( len(magicSquare) ))
    if ( size < 3 ):
        return False

    # Get the Magic Sum Constant 
    magicConstant = ( size * (size**2 + 1) ) / 2

    # Validate
    for x in range( 0, size ):
        #Check Rows
        if ( sum(magicSquare[x*size : x*size+size]) <> magicConstant ):
             return False

        # Check Columns
        if ( sum(magicSquare[ x :: size ]) != magicConstant ):
             return False

    # Check Diagonal
    if ( sum( magicSquare[ 0 :: size+1 ] ) != magicConstant or
         sum( magicSquare[ -1 :: -(size+1) ] ) != magicConstant ):
        return False

    # Success
    return True

##### MAIN #####

def main():
    squaresList = [ [8, 1, 6, 3, 5, 7, 4, 9, 2],    #==> True
                    [2, 7, 6, 9, 5, 1, 4, 3, 8],    #==> True
                    [3, 5, 7, 8, 1, 6, 4, 9, 2],    #==> False
                    [8, 1, 6, 7, 5, 3, 4, 9, 2],    #==> False
                    [1, 15, 14, 4, 12, 6, 7, 9,
                     8, 10, 11, 5, 13, 3, 2, 16],   #==> True
                    [1, 15, 14, 4, 12, 7, 6, 9,
                     8, 10, 11, 5, 13, 3, 2, 16] ]  #==> False
    

    for ls in squaresList:
        print( ls )
        if ( validateSquare(ls) ):
             print( "  True" )
        else:
             print( "  False" )

##### RUN MAIN #####

if ( __name__ == "__main__" ):
    main()
