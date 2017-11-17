# Strategy Guide

## Strategy indicator for TradeStation

Very basic strategy that enters on swing high/low and exits on Stochastic FullD
### Chart Strategy
Plots theoretical buy/sell orders on a chart. This can be used to automate the execution of trades, both in a simulated account as well as in a live account. User assumes all risk. This code is provided for educational purposes only and and it NOT intended to generate profits. **No, seriously, the code is only provided so you can learn how all the pieces work together. You are responsible to take this knowledge and perform your own analysis, and create your own strategies.**

## Getting Started
#### Installation Method #1:

The DLL file included:
```
HT_StratGuide.dll
```
1. Simply download the DLL file and save to your hard drive. 
1. Open the Data folder located inside your Sierra Chart installation directory.
1.1 Typically located at: C:\SierraChart\Data
1. Copy/Paste the DLL file into the DATA folder of Sierra Chart. 
1. If open, close Sierra Chart application and reopen it.
1. The study is now available to add to your charts. Located under "Add Custom Study". 
1.1 The study is located under the heading: Strategy Guide DLL and the name of the study is StrategyGuide.

#### Installation Method #2 (advanced users):

**!!!IT IS HIGHLY RECOMMENDED THAT YOU FOLLOW INSTALL METHOD #1**

Source code is provided in the form of the following a text files:

**Source code for the chart strategy**
```
strat-guide.cpp
```

1. Download the .cpp file to your hard drive.
1. Copy/Paste the file into the Source folder inside your Sierra Chart installation directory.
1.1 Typically located at: C:\SierraChart\Source.
1. Open Sierra Chart Application and click the Analysis menu at the top of the program window.
1. Select "Build Custom Study DLL's" from that menu. 
1. Click the button "Select Files(s)" then scroll to and select the file named strat-guid.cpp and cick "Open".
1. Click the button "Build Custom Studies DLL". 
1. The study is now available to add to your charts. Located under "Add Custom Study". 
1.1 The study is located under the heading: Strategy Guide DLL and the name of the study is StrategyGuide.

### Prerequisites

#### *Charges May Apply

*Requires you to install the [TradeStation platform](https://www.tradestation.com/)

### Additional file
Contains theoretical trade data exported from TradeStation.
```
StratAnalysis.ods
```
### Detailed video demo showing installation and settings

[![Comming Soon](https://www.hahn-tech.com/wp-content/uploads/2017/09/logo-site-icon.jpg)](https://www.youtube.com/watch?)

## Contributing

Please read CONTRIBUTING.md for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Pete Hahn** - *Initial work* - [HahnTech](https://github.com/hahntech)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the GNU GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details
