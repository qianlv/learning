## Copyright (C) 2017 qianlv
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} selectThreshold (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2017-01-06

function [bestEpsilon, bestF1] = selectThreshold (yval, pval)
    bestEpsilon = 0;
    bestF1 = 0;
    F1 = 0;

    stepsize = (max(pval) - min(pval)) / 1000;
    for epsilon = min(pval):stepsize:max(pval)
        cvPredictions = pval < epsilon;
        tp = sum((cvPredictions == 1) & (yval == 1));
        fp = sum((cvPredictions == 1) & (yval == 0));
        fn = sum((cvPredictions == 0) & (yval == 1));
        prec = tp / (tp + fp + 1e-10);
        rec = tp / (tp + fn + 1e-10);
        F1 = 2 * prec * rec / (prec + rec + 1e-10);
        if bestF1 < F1
            bestF1 = F1;
            bestEpsilon = epsilon;
        end
    end
endfunction
