from django.shortcuts import render
from django.http import JsonResponse, HttpResponse
import json
from .models import User, Message
from django.core.exceptions import ValidationError

# Create your views here.
def message(request):
    def gen_response(code: int, data: str):
        return JsonResponse({
            'code': code,
            'data': data
        }, status=code)

    # GET的完整实现已经给出，同学们无需修改
    if request.method == 'GET':
        limit = request.GET.get('limit', default='100')
        offset = request.GET.get('offset', default='0')
        if not limit.isdigit():
            return gen_response(400, '{} is not a number'.format(limit))
        if not offset.isdigit():
            return gen_response(400, '{} is not a number'.format(offset))

        return gen_response(200, [
                {
                    'title': msg.title,
                    'content': msg.content,
                    'user': msg.user.name,
                    'timestamp': int(msg.pub_date.timestamp())
                }
                for msg in Message.objects.all().order_by('-pk')[int(offset) : int(offset) + int(limit)]
            ])

    elif request.method == 'POST':
        # 从cookie中获得user的名字，如果user不存在则新建一个
        # 如果cookie中没有user则使用"Unknown"作为默认用户名
        name = request.COOKIES['user'] if 'user' in request.COOKIES else 'Unknown'
        user = User.objects.filter(name=name).first()
        if not user:
            user = User(name = name)
            try:
                # 注意在调用full_clean()时Django会自动检测字段的有效性，这个有效性检测包括检测CharField是否满足最大长度限制
                user.full_clean()
                # 存入数据库
                user.save()
            except ValidationError as e:
                return gen_response(400, "Validation Error of user: {}".format(e))


        # 验证请求的数据格式是否符合JSON规范(请求体可通过json.loads()即可），如果不符合则返回code 400，data字段内容自定义即可
		# --------------------------------------------------------------------------------------------
        try:
            jsonObj = json.loads(request.body.decode())
        except ValueError as e:
            return gen_response(400, f"request body {request.body} is not a JSON Object")

        # 验证请求数据是否满足接口要求，若通过所有的验证，则将新的消息添加到数据库中。如果不符合要求则返回code 400，data字段内容自定义即可
        # PS: 请求数据体应该为{"title": "something", "content": "someting"} ，请确保title和content字段存在，并且title和content均有最大长度限制
		# PS: 检测方式可以参考user，使用Django提供的full_clean()方法进行检测
        # --------------------------------------------------------------------------------------------
        title = jsonObj.get('title')
        content = jsonObj.get('content')
        if title is None:
            gen_response(400, 'title not exist')
        if content is None:
            gen_response(400, 'content not exist')
        message = Message(user=user, title=title, content=content)
        try:
            message.full_clean()
            message.save()
        except ValidationError as e:
            return gen_response(400, 'message length is too long')

        # 添加成功返回code 201
        return gen_response(201, "message was sent successfully")

    else:
        return gen_response(405, 'method {} not allowd'.format(request.method))
