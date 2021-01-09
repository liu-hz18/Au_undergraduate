from django.test import TestCase, Client
from .models import Message, User
# Create your tests here.

class MessageModelTests(TestCase):
    def setUp(self):
        alice = User.objects.create(name="Alice")
        bob = User.objects.create(name="Bob")

        Message.objects.create(user=alice, title="Hi", content="Hello World!")
        Message.objects.create(user=bob, title="This is a title", content="This is my content")

    def add_new_message(self, title=None, content=None, user=None):
        payload = {
            'title': title,
            'content': content
        }

        payload_remove_none = {}
        for i in payload:
            if payload[i] is not None:
                payload_remove_none[i] = payload[i]

        if user is not None:
            self.client.cookies['user'] = user

        return self.client.post('/api/message', data=payload_remove_none, content_type="application/json")

    def test_message_can_be_fetched(self):  
        offset, limit = 0, 100  
        response_data = [
                {
                    'title': msg.title,
                    'content': msg.content,
                    'user': msg.user.name,
                    'timestamp': int(msg.pub_date.timestamp())
                }
                for msg in Message.objects.all().order_by('-pk')[int(offset) : int(offset) + int(limit)]
            ]
        response = self.client.get("/api/message")
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.json()['data'], response_data)
       
        
    def test_add_new_message(self):
        title = "Test Title"
        content = "My test message"
        user = 'Student'

        response = self.add_new_message(title, content, user)
        self.assertJSONEqual(response.content, {'code': 201, 'data': 'message was sent successfully'})
        self.assertTrue(User.objects.filter(name="Student").exists())
        self.assertTrue(Message.objects.filter(title=title, content=content).exists())

    
    def test_message_title_lost(self):
        content = "Test Content"
        user = 'Student'

        response = self.add_new_message(content=content, user=user)
        self.assertEqual(response.status_code, 400)

    
    def test_message_content_lost(self):
        title = "Test Title"
        user = 'Student'

        response = self.add_new_message(title=title, user=user)
        self.assertEqual(response.status_code, 400)

    
    def test_user_name_too_long(self):
        title = "Test Title"
        content = "My test message"
        user = 'Student' * 100
        
        response = self.add_new_message(title=title, content=content, user=user)
        self.assertEqual(response.status_code, 400)

    
    def test_content_too_long(self):
        title = "Test Title"
        content = "My test message" * 1000
        user = 'Student'

        response = self.add_new_message(title=title, content=content, user=user)
        self.assertEqual(response.status_code, 400)

    
    def test_unknown_user(self):
        title = "Test Title"
        content = "My test message"

        response = self.add_new_message(title=title, content=content)
        self.assertEqual(response.status_code, 201)
        self.assertTrue(Message.objects.filter(title=title, content=content).exists())
        self.assertTrue(Message.objects.filter(user__name="Unknown").exists())
