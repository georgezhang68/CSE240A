//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include "predictor.h"

//
// TODO:Student Information
//
const char *studentName = "NAME";
const char *studentID   = "PID";
const char *email       = "EMAIL";

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *bpName[4] = { "Static", "Gshare",
                          "Tournament", "Custom" };

int ghistoryBits; // Number of bits used for Global History
int lhistoryBits; // Number of bits used for Local History
int pcIndexBits;  // Number of bits used for PC index
int bpType;       // Branch Prediction Type
int verbose;

uint8_t taken_or_not_taken(uint8_t symbol)
{
    if (symbol == WT || symbol == ST) {
        return TAKEN;
    } else {
        return NOTTAKEN;
    }
}

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

//
//TODO: Add your own Branch Predictor data structures here
//


//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

//------------------------------------//
//              GShare                //
//------------------------------------//

/*
    Gshare Data Structures
*/
uint8_t* gShareTable;       // size = 2^ghistoryBits
uint32_t gShareHistoryReg;
uint32_t gShareMask;

/*
    Gshare Init
*/
void init_gshare_predictor()
{
    uint32_t tableSize = 1 << ghistoryBits;
    gShareTable = (uint8_t*) malloc(tableSize * sizeof(uint8_t));
    gShareHistoryReg = 0;
    gShareMask = tableSize - 1;
    for (int i = 0; i < tableSize; i++) {
        gShareTable[i] = WN;
    }
}

/*
    Gshare Make
*/
uint8_t
make_gshare_prediction(uint32_t pc)
{
    uint32_t index = (pc ^ gShareHistoryReg) & gShareMask;
    if (taken_or_not_taken(gShareTable[index])) {
        return TAKEN;
    } else {
        return NOTTAKEN;
    }
}

/*
    Gshare Train
*/
void
train_gshare_predictor(uint32_t pc, uint8_t outcome)
{
    uint32_t index = (pc ^ gShareHistoryReg) & gShareMask;
    gShareHistoryReg = ((gShareHistoryReg << 1) ^ outcome) & gShareMask;
    if (outcome == TAKEN && gShareTable[index] != ST) {
        gShareTable[index]++;
    } else if (outcome == NOTTAKEN && gShareTable[index] != SN) {
        gShareTable[index]--;
    }
}

/*-----------------------------------*/


// Initialize the predictor
//
void
init_predictor()
{
  //
  //TODO: Initialize Branch Predictor Data Structures
  //
  switch(bpType) {
    case STATIC:
        break;
    case GSHARE:
        init_gshare_predictor();
        break;
    case TOURNAMENT:
    case CUSTOM:
    default:
      break;
  }
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t
make_prediction(uint32_t pc)
{
  //
  //TODO: Implement prediction scheme
  //

  // Make a prediction based on the bpType
  switch (bpType) {
    case STATIC:
        return TAKEN;
    case GSHARE:
        return make_gshare_prediction(pc);
        break;
    case TOURNAMENT:
        break;
    case CUSTOM:
        break;
    default:
      break;
  }

  // If there is not a compatable bpType then return NOTTAKEN
  return NOTTAKEN;
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void
train_predictor(uint32_t pc, uint8_t outcome)
{
  //
  //TODO: Implement Predictor training
  //
    
    switch (bpType) {
    case STATIC:
        break;
    case GSHARE:
        train_gshare_predictor(pc, outcome);
        break;
    case TOURNAMENT:
        break;
    case CUSTOM:
        break;
    default:
      break;
  }
}
