load('ex4data1.mat');
mySelection = [1800 600];%600 1800 2500 4500 3500 4000];
%data = X(mySelection,:);
%data = round(data).*2 - 1;
data = round(rand(10,100)).*2 - 1;

displayData(data);
W=data'*data;
for i = 1:size(W,1)
    W(i,i) = 0;
end

origData = data;

for i = 1:size(data, 1)
    for j = 1:size(data, 2)
        if rand() < 0.6
            data(i, j) = -1*data(i, j);
        end
    end
end

toDisplay = [];
for i = 1:size(data, 1)
    toDisplay = [toDisplay; data(i, :)];
    sm1 = zeros(1, size(data, 2));
    s = data(i, :);
    while not(isequal(s, sm1))
        %-1/2*(s*W*s')
        sm1 = s;
        s = sign(s*W + 0.001);
    end
    toDisplay = [toDisplay; origData(i, :)];
    toDisplay = [toDisplay; s];
    toDisplay = [toDisplay; s == origData(i, :)];
end
displayData(toDisplay);