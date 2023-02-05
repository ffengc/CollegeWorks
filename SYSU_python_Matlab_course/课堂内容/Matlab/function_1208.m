
% function 1
function output = myFunction(input)
    switch input
        case -1
            output = 'nagative one';
        case 0
            output = 'zero';
        case 1
            output = 'positive one';
        otherwise
            output = 'other value';
    end
end


% 计算1~10，3~10，7~10之前所有数字之和
function sum = Cal_sum(s_num,e_num)
    sum = 0;
    for i = s_num:e_num
        sum = sum+i;
    end
end