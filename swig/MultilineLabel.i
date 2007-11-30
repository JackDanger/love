
namespace love
{
	class MultilineLabel : public Label
	{
	protected:
	public:
		//MultilineLabel(const string & caption = "");
		//virtual ~MultilineLabel();

		//virtual void setCaption(const string & caption);

		virtual int adjustContent();
		virtual void adjustSize();
	};

	typedef boost::shared_ptr<MultilineLabel> pMultilineLabel;
}

// Extensions
%extend love::MultilineLabel {

	void setCaption(const char * caption)
	{
		self->setCaption(string(caption));
	}

};