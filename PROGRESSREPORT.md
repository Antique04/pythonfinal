# Status Report

#### Your name

Anthony Eckert and Isaac Kraus

#### Your section leader's name

Jeremy Fan

#### Project title

Taco Bell Synth

***

Short answers for the below questions suffice. If you want to alter your plan for your project (and obtain approval for the same), be sure to email your section leader directly!

#### What have you done for your project so far?

We found the framework to use for our synth, a programming language based on AngelScript called Plug'N Script which is used to make VSTs. 
We initially planned to make a synth without any real specificity, but we have pivoted to aiming to recreate the iconic taco bell "bong" noise. We researched and learned that this noise is from a Yamaha DX7, so we found this original preset online and are hoping to reverse engineer it. We have a working synth in the language (based initially on a plugin) and are working to modify its noise. We also have a very basic GUI. 

#### What have you not done for your project yet?

The next stage is to code in the dsp script for the actual synth, using our understanding of the way the original sound is achieved we can reverse engineer it and execute it through raw code in our script.

#### What problems, if any, have you encountered?

We initially wanted to program a plugin from scratch but quickly realized this was out of the scope of the project as neither of us know C++ and Python is not widely adopted for VSTs. However, the framework we are using lacks some documentation, so we have struggled a bit understanding how it works, but we are continuing to work on it. 
