var http = require("http");
var url = require("url");
var fs = require("fs");

var serve = http.createServer(function(req, res){
		console.log("req.url : " + req.url);
		var req_path = url.parse(req.url).path;
     	console.log("req_path : " + req_path);
     	var filepath = __dirname + req_path;
     	console.log("filepath : " + req_path);
     	fs.exists(filepath, function(exists){
 			if(exists){
 				console.log("请求文件存在 : " + filepath);
 				var f = fs.createReadStream(filepath);
 				var size = fs.statSync(filepath).size;
 				var name = "version.txt";
 				res.writeHead(200, {
    				'Content-Type': 'application/force-download',
    				'Content-Disposition': 'attachment; filename=' + name,
    				'Content-Length': size
  				});
 				f.pipe(res);
 			}else{
 				res.writeHead(404, {'Content-Type' : 'text/html;charset=utf8'});
            	res.end('<div styel="color:black;font-size:22px;">404 not found</div>');
 			}

     	});
	});

serve.listen('9090', '127.0.0.1');