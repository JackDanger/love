/* File : love.i */
%module love

%runtime %{
%}

%header %{
%}

%wrapper %{
%}

%init %{
%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

%include Color.i

%include Device.i

// Graphical
%include Font.i
%include Sprite.i
%include Image.i
%include Animation.i
%include Particlesystem.i
%include Graphics.i

// Audio
%include Sound.i
%include Music.i
%include Audio.i

// Filesystem
%include Filesystem.i

%include Timer.i
%include Mouse.i
%include Keyboard.i

// Constants
%include love_constants.i

// Global "devices".
// These eventually end up as love.graphics, love.audio, etc.
%include love_devices.i

// love.objects
%include objects.i