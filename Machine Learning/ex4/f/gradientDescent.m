function [nn_params, costs] = gradientDescent(costFunction, initial_nn_params, alfa)
%GRADIENTDESCENT Summary of this function goes here
%   Detailed explanation goes here
nn_params = initial_nn_params;
costs = [];
for i = 1 : 100
    [J, grad] = costFunction(nn_params);
    nn_params = nn_params - alfa*grad;
    costs = [costs;J];
end
end

