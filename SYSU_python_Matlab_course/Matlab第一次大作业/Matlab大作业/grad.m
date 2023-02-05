function   [k,f1,f2,f3] = grad(f,x1,x2,s,start_point,thereshold) 
    k = 0;%迭代次数赋值初始化
    grad_f = [diff(f,x1) diff(f,x2)]; %计算f的梯度 
    delta = subs(grad_f,[x1,x2],[start_point(1),start_point(2)]);
    %计算起点的梯度   
    step=1; %设置初始步长为1
    current_point = start_point;%起点值赋给当前点
    %最速下降法的主循环，判断条件为：梯度的模与所给精度值进行比较
    while norm(delta) > thereshold          
        k = k + 1;%迭代次数+1     
        %一维探索 求最优步长（此时方向已知，步长s为变量）
        x_next = [current_point(1),current_point(2)] - s* delta/norm(delta);% 计算x（k+1）点，其中步长s为变量 
        f_val = subs(f,[x1,x2],[x_next(1),x_next(2)]);% 将x值带入目标函数中
        step = abs(double(solve(diff(f_val,s)))); % 对s求一阶导，并加绝对值符号，得到最优步长的绝对值
        step = step(1);%更新步长    
        %计算x（k+1）点
        current_point = double([current_point(1),current_point(2)] - step * delta/norm(delta));
        %计算x（k+1）点的梯度值
        delta = subs(grad_f,[x1,x2],[current_point(1),current_point(2)]);
        %计算函数值
        f_value = double(subs(f,[x1,x2],[current_point(1),current_point(2)]));
        %输出迭代计算过程
        result_string=sprintf('k=%d, x1=%.6f, x2=%.6f, step=%.6f f(x1,x2)=%.6f',k,current_point(1),current_point(2),step,f_value);
        f1(k)=current_point(1);
        f2(k)=current_point(2);
        f3(k)=f_value;
        disp(result_string);
    end
end

