# 关于用原生ajax请求接口数据的一些问

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>原生AJAX请求新闻数据</title>
    <style>
        .news{
            display: flex;
            background: #f4f4f4;
            padding: 10px;
            margin-bottom: 10px;
        }
        .news ul{
            list-style: none;
        }
    </style>
</head>
<body>
    
    <button id="button">请求接口</button>
    <br><br>
    <h1>所有新闻信息</h1>
    <div id="things"></div>
    <script>
        document.getElementById("button").addEventListener("click",loadNews);
        function loadNews () {
            var xhr = new XMLHttpRequest();
            xhr.open("GET","https://api.apiopen.top/getWangYiNews?result",true);
            xhr.onload = function (){
                if(this.status == 200) {
                    var news = JSON.parse(this.responseText)["result"];
                    console.log(news); 
                    var outPut = '';
                    for(var i in news){
                        outPut += `
                            <div class="news"> 
                                <img src="${news[i].image}" width="70" height="70"/>    
                                <ul>
                                    <li>TITLE: ${news[i].title}</li>
                                    <li>PATH: ${news[i].path}</li>
                                    <li>PASSTIME: ${news[i].passtime}</li>
                                </ul>
                            </div>    
                         `;
                    }
                    document.getElementById("things").innerHTML = outPut;
                }
            }
            xhr.send();
        }
    </script>
</body>
</html>

```

```html
 var news = JSON.parse(this.responseText)["result"];
```

这里在转换字符时，对语句要求比较严格，建议多进行百度

### 如要进行对表格整体数据中个别数据的转换，要参照相应的语句

