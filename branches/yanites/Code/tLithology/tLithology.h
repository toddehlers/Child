//-*-c++-*- 

/**************************************************************************/
/**
**  @file tLithology.h
**  @brief Header file for the tLithology class
**
**  Class tLithology represents the lithology
**  across a terrain. Class tLithology is designed to embed in a node (
**  similar to tVegCover) the local erodibility parameters kd and kf
**
**
**  Created Feb, 2012, BJY
**  
**
*/
/**************************************************************************/



#ifndef TLITHOLOGY_H
#define TLITHOLOGY_H

#include <math.h>
#include <vector>

#include "../tInputFile/tInputFile.h"
//#include "../tMesh/tMesh.h"
template<class tLNode> class tMesh;

class tLithology
{
	public:
	 tLithology();
	 tLithology( tMesh<class tLNode> *, const tInputFile & );
	 void UpdateLithology( tMesh<class tLNode> *, double delt);
	 void SetRockErodibility(tMesh<class tLNode> *, tArray< double > erody); //check this, erody is defined blow on line 72
	 // void   FUNCTIONS HERE
	 
	private:
      double mdKdL;   // Lcoal hillslope diffusion term
      double mdKbL;  // Local fluvial erodibility term
      int miMaxNumUnits; //Maximum number of layers for a given node, can be greater than the number of rock types for folded units
      int miNumLithologies; //Number of lithologies defined in the domain (less than or equal to miMaxNumUnits);
//      double miLithologyMapDepthInterval; //Depth interval between lithology maps
//      tArray<double> mLithologyMapDepths; //Depth corresponding to each lithology map
//      char mLithologyMapFilename[120];
//      double MapDepth;
    
    
      tArray<int> mCurrentLithoMap; //current map number
      tArray<double> mElevNextLithoMap; //elevation of the next lithology map for each node
     
      char mPropertyLookUpFilename[120];
      char mLithoBaseElevationFilename[120];
      char mLithoUnitOrderFilename[120];
     
//      tArray<int> CurrentLithoIndex; //current index of lithology unit and base elevation
//      tArray<int> CurrentLithoUnit;  //current integer lihtology unit value to use in look up table
//      tArray<double> NextContactDepth; //depth to the next change in lithology
      int numlithounits;
      double LocContactDepths;
      int LocUnitList;
//      tArray<double> UnitList;
//	  double UnitList[size];
      tArray<double> KDLookupTable;
      tArray<double> KBLookupTable;
      tArray<double> SedDensityLookupTable;
      tArray<double> SedRockFlagLookupTable;
      tArray<double> DgradeLookupTable;

      tArray<double> erody;

   		tMesh<tLNode> *meshPtr;    // ptr to mesh

      
};



#endif