function CreateTXT(in, filename)
fileID = fopen(filename, 'w');
fprintf(fileID, '%f ', in);
fclose(fileID);
end

