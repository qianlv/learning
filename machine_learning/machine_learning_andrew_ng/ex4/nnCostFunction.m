## Copyright (C) 2016 qianlv
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
## @deftypefn {Function File} {@var{retval} =} nnCostFunction (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2016-12-30

function [J, grad] = nnCostFunction (nn_params, input_layer_size, hidden_layer_size, ...
                              num_labels, X, y, lambda)
    theta1 = reshape(nn_params(1: hidden_layer_size * (input_layer_size + 1)), ...
                     hidden_layer_size, input_layer_size + 1);
    theta2 = reshape(nn_params(hidden_layer_size * (input_layer_size + 1) + 1 : end), ...
                     num_labels, hidden_layer_size + 1);
    X = [ones(size(X, 1), 1) X];
    a1 = X;
    z2 = a1 * theta1';
    a2 = sigmoid(z2);
    a2 = [ones(size(a2, 1), 1) a2];
    z3 = a2 * theta2';
    a3 = sigmoid(z3);

    Y = eye(num_labels)(y, :);
    
    m = size(X, 1);
    cost = Y .* log(a3) + (1 - Y) .* log(1 - a3);
    J = -sum(sum(cost)) / m + ...
        lambda / 2 / m * (sum(sum(theta1(:, 2:end) .^ 2)) + sum(sum(theta2(:, 2:end) .^ 2)));

    
    Theta1_grad = zeros(size(theta1));
    Theta2_grad = zeros(size(theta2));
    
    delta3 = a3 - Y;
    delta2 = (delta3 * theta2)(:, 2:end) .* sigmoidGradient(z2);
    Theta1_grad = delta2' * a1 / m + [zeros(hidden_layer_size, 1) theta1(:, 2:end)] * lambda / m;
    Theta2_grad = delta3' * a2 / m + [zeros(num_labels, 1) theta2(:, 2:end)] * lambda / m;
    grad = [Theta1_grad(:); Theta2_grad(:)];
    % D1 = zeros(size(theta1));
    % D2 = zeros(size(theta2));
    % for t = 1:m,
        % ra1 = X(t, :)';
        % rz2 = theta1 * ra1;
        % ra2 = sigmoid(rz2);
        % ra2 = [1; ra2];
        % rz3 = theta2 * ra2;
        % ra3 = sigmoid(rz3);

        % err3 = ra3 - Y(t, :)';
        % err2 = (theta2' * err3)(2:end, 1) .* sigmoidGradient(rz2);
        % D1 = D1 + err2 * ra1';
        % D2 = D2 + err3 * ra2';
    % end
    % D1 = D1 / m + [zeros(hidden_layer_size, 1) theta1(:, 2:end)] * lambda / m;
    % D2 = D2 / m + [zeros(num_labels, 1) theta2(:, 2:end)] * lambda / m;

    % grad = [D1(:); D2(:)];
endfunction
