
#include "sierrachart.h"

// For reference, refer to this page:
// https://www.sierrachart.com/index.php?page=doc/AdvancedCustomStudyInterfaceAndLanguage.php

// This line is required. Change the text within the quote
// marks to what you want to name your group of custom studies.
SCDLLName("Strategy Guide DLL")



SCSFExport scsf_StratGuide(SCStudyInterfaceRef sc) {
	SCInputRef kPeriod = sc.Input[0];
	SCInputRef dPeriod = sc.Input[1];
	SCInputRef smoothingPeriod = sc.Input[2];
	SCInputRef averageType = sc.Input[3];
	SCInputRef inputPriceHigh = sc.Input[4];
	SCInputRef inputPriceLow = sc.Input[5];
	SCInputRef inputPriceClose = sc.Input[6];

	SCSubgraphRef slowD = sc.Subgraph[0];
	//SCSubgraphRef fullK = sc.Subgraph[1];
	SCSubgraphRef stoch = sc.Subgraph[2];
	SCFloatArrayRef priceH = sc.Subgraph[3];
	SCFloatArrayRef priceL = sc.Subgraph[4];
	SCFloatArrayRef priceC = sc.Subgraph[5];
	SCFloatArrayRef pivotLow = sc.Subgraph[6];
	SCFloatArrayRef pivotHigh = sc.Subgraph[7];
	SCSubgraphRef pivotLowReversal = sc.Subgraph[8];
	SCSubgraphRef pivotHighReversal = sc.Subgraph[9];
	SCSubgraphRef exitLong = sc.Subgraph[10];
	SCSubgraphRef exitShort = sc.Subgraph[11];
	
	

	// Section 1 - set config defaults
	if (sc.SetDefaults) {
		sc.GraphName = "Strategy Guide";
		sc.GraphRegion = 0;// plot in upper price graph (comment out to plot in lower subgraph)

		sc.StudyDescription = "Basic entry/exit code used with spreadsheet systems";
		sc.AutoLoop = 1; // automatic looping
		sc.FreeDLL = 1; // 1 is for development

		kPeriod.Name = "K Period";
		kPeriod.SetInt(10);

		dPeriod.Name = "K Period";
		dPeriod.SetInt(10);

		averageType.Name = "Moving Avg Type";
		averageType.SetMovAvgType(MOVAVGTYPE_SIMPLE);

		inputPriceHigh.Name = "Input Data For High";
		inputPriceHigh.SetInputDataIndex(SC_HIGH);

		inputPriceLow.Name = "Input Data For Low";
		inputPriceLow.SetInputDataIndex(SC_LOW);

		inputPriceClose.Name = "Input Data For Close";
		inputPriceClose.SetInputDataIndex(SC_LAST);

		smoothingPeriod.Name = "Smoothing Period";
		smoothingPeriod.SetInt(3);


		/*fullD.Name = "FullD";
		fullD.DrawStyle = DRAWSTYLE_LINE;
		fullD.LineWidth = 2;
		fullD.PrimaryColor = RGB(255, 0, 0);*/

		pivotLowReversal.Name = "Long Entry";
		pivotLowReversal.DrawStyle = DRAWSTYLE_ARROWUP;

		pivotHighReversal.Name = "Short Entry";
		pivotHighReversal.DrawStyle = DRAWSTYLE_ARROWDOWN;

		exitLong.Name = "Long Exit";
		exitLong.DrawStyle = DRAWSTYLE_ARROWDOWN;

		exitShort.Name = "Short Exit";
		exitShort.DrawStyle = DRAWSTYLE_ARROWUP;

		return;
	}

	// Section 2 - Perform calculations here
	try {
		// load enough historical bars on the chart to initialize the stochastic elements
		sc.DataStartIndex = kPeriod.GetInt() + kPeriod.GetInt() + smoothingPeriod.GetInt();
		// get the stochastic elements
		sc.Stochastic(
			sc.BaseData[inputPriceHigh.GetInputDataIndex()],
			sc.BaseData[inputPriceLow.GetInputDataIndex()],
			sc.BaseData[inputPriceClose.GetInputDataIndex()],
			stoch,
			kPeriod.GetInt(),
			dPeriod.GetInt(),
			smoothingPeriod.GetInt(),
			averageType.GetMovAvgType()
			);
		// only using FullD here
		slowD[sc.Index] = stoch.Arrays[1][sc.Index];

		// set the HLC elements for price pattern detection
		priceH = sc.BaseData[SC_HIGH];
		priceL = sc.BaseData[SC_LOW];
		priceC = sc.BaseData[SC_LAST];

		// build the signals that are based on price action patterns
		pivotLow[sc.Index] = priceL[sc.Index] > priceL[sc.Index - 1] && 
			priceL[sc.Index - 1] < priceL[sc.Index - 2] && 
			priceL[sc.Index - 2] < priceL[sc.Index - 3];
		pivotHigh[sc.Index] = priceH[sc.Index] < priceH[sc.Index - 1] &&
			priceH[sc.Index - 1] > priceH[sc.Index - 2];
		if (
			(pivotLow[sc.Index] && priceC[sc.Index] > priceH[sc.Index - 1]) ||
			(pivotLow[sc.Index - 1] && priceC[sc.Index] > priceH[sc.Index - 2] &&
				priceL[sc.Index] > priceL[sc.Index - 2] &&
				priceH[sc.Index - 1] < priceH[sc.Index - 2])
			) {
			pivotLowReversal[sc.Index] = priceL[sc.Index];
		}
		else {
			pivotLowReversal[sc.Index] = 0.0;
		}
		if (
			slowD[sc.Index] < slowD[sc.Index - 1] &&
			slowD[sc.Index - 1] < slowD[sc.Index - 2] &&
			pivotLowReversal[sc.Index] == 0 && pivotLowReversal[sc.Index - 1] == 0
			) {
			exitLong[sc.Index] = priceH[sc.Index];
		}
		else {
			exitLong[sc.Index] = 0.0;
		}
		if (
			(pivotHigh[sc.Index] &&
				priceC[sc.Index] < priceL[sc.Index - 1]) ||
				(pivotLow[sc.Index - 1] && priceC[sc.Index] < priceL[sc.Index - 2] &&
					priceH[sc.Index] < priceH[sc.Index - 2] &&
					priceL[sc.Index - 1] > priceL[sc.Index - 1] > priceL[sc.Index - 2])
			) {
			pivotHighReversal[sc.Index] = priceH[sc.Index];
		}
		else {
			pivotHighReversal[sc.Index] = 0.0;
		}
		if (
			slowD[sc.Index] > slowD[sc.Index - 1] &&
			slowD[sc.Index - 1] > slowD[sc.Index - 2] &&
			pivotHighReversal[sc.Index] == 0 && pivotHighReversal[sc.Index - 1] == 0
			) {
			exitShort[sc.Index] = priceL[sc.Index];
		}
		else {
			exitShort[sc.Index] = 0.0;
		}
	}
	catch (char *ErrMsg) {
		sc.AddMessageToLog(ErrMsg, 1);
	}
}