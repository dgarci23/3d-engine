image = imread("david.jpg");

resized_img = imresize(image, [240 320]);

[x, map] = rgb2ind(resized_img, 4);

imshow(x, map);

color_field = dec2hex(double(map*255));
x = dec2hex(double(x)); 

writematrix(x, "../verilog/background.txt", "Delimiter", " ");
writematrix(color_field, "../verilog/colors.txt", "Delimiter", " "); 